cmake_minimum_required(VERSION 3.26)
Project(design_analysis)
# file(GLOB_RECURSE SRC "./src/*.cpp" "./src/*.c")

include_directories("./"
                    "./include")
link_directories("./lib/gdstk")
list(APPEND STATIC_LIBS libgdstk.a)

add_executable(exec_design main.cpp)
# add_executable(exec_design example_basic_geometry.cpp)
# add_executable(exec_design example_reference.cpp)
target_link_libraries(exec_design ${STATIC_LIBS} qhull_r z pthread "-Wl,--rpath=${ORIGIN}")

# add_custom_command(
#     TARGET exec_renderer
#     #  COMMAND cp -rf build/exec_renderer bin/exec_renderer
#     COMMAND cp -rf build/exec_renderer bin/renderer
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )