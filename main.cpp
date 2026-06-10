#include <stdio.h>
#include <string>

#include "spdlog/spdlog.h"
#include "gdstk/gdstk.hpp"

using namespace std;
using namespace gdstk;

void PrintUsage(int exit_code)
{
    printf(R"(Usage: exec_design design_file
    design_file       must be gds/oas

Example:
    ./exec_design test.gds
    ./exec_design test.oas

)");
    exit(exit_code);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        spdlog::error("Lack of neccessary input\n");
        PrintUsage(-1);
    }

    ErrorCode err_code;

    string input_file = argv[1];

    Library lib = {};

    if (input_file.size() >= 4)
    {
        if (input_file.compare(input_file.size() - 4, 4, ".gds") == 0)
        {
            lib = read_gds(input_file.c_str(), 0, 1e-9, NULL, &err_code);
        }
        else if (input_file.compare(input_file.size() - 4, 4, ".oas") == 0)
        {
            lib = read_oas(input_file.c_str(), 0, 1e-9, &err_code);
        }
        else
        {
            spdlog::error("Unspported input_file {}", input_file);
            PrintUsage(-1);
        }
    }
    else
    {
        spdlog::error("Unspported input_file {}\n", input_file);
        PrintUsage(-1);
    }


    if (err_code != ErrorCode::NoError)
    {
        spdlog::error("Failed to open the input file {} {}\n", input_file, (int)err_code);
        exit(EXIT_FAILURE);
    }

    lib.print(true);
    printf("\n");

    for (size_t i_cell = 0; i_cell < lib.cell_array.count; i_cell++)
    {
        Cell *cell = lib.cell_array[i_cell];

        cell->print(true);
        printf("\n");

        Array<Reference *> array_ref;
        cell->flatten(true, array_ref);
        for (size_t i_ref = 0; i_ref < array_ref.count; i_ref++)
        {
            Reference *ref = array_ref[i_ref];
            ref->print();
            printf("\n");
        }

        for (size_t i_poly = 0; i_poly < cell->polygon_array.count; i_poly++)
        {
            Polygon *poly = cell->polygon_array[i_poly];

            poly->print(true);
            printf("\n");
        }
    }

    return 0;
}