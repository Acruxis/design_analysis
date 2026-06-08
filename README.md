# Design Analysis By GDSTK<br/>

## Main Struct<br/>

```PliantText
Library (版图大库 / 根节点)
 └── unit, precision (物理单位与物理精度)
 └── cell_array (Cell 指针动态数组)
      └── Cell (版图单元 / 核心中间节点)
           ├── name (单元名称，如 "TopCell", "INV_X1")
           │
           ├── polygon_array (多边形指针数组 ── 核心物理几何体)
           │    └── Polygon (多边形实体)
           │         ├── tag (由 make_tag 产生的 layer 和 datatype)
           │         └── point_array (Vec2 顶点数组 ── 存储真实浮点坐标)
           │
           ├── flexpath_array / robustpath_array (连续路径数组 ── 对应导线)
           │    └── FlexPath / RobustPath (路径实体)
           │         └── 最终写出时会被离散、粉碎并倒出为大量的 Polygon
           │
           ├── label_array (文本标注数组 ── 非物理几何体，用于引脚和注释)
           │    └── Label (文本节点，包含坐标和 String)
           │
           └── reference_array (实例引用数组 ── 实现版图复用与层级嵌套的关键)
                └── Reference (引用节点)
                     ├── cell (指向另一个 Cell 的指针 ── 形成图的拓扑网络)
                     ├── origin (实例化时的偏移原点)
                     ├── rotation, magnify, x_reflection (旋转、放大、翻转等仿射变换参数)
                     └── repetition (用于 AREF 阵列引用的重复排列参数)
```
<br/>

## Support Struct

```PliantText
gdstk 辅助工具箱 (计算级数据结构)
 │
 ├── Vec2 (最底层的双精度浮点数二元组：struct { double x; double y; })
 │    └── 全局所有几何体（Polygon, Curve, Reference）的基石坐标
 │
 ├── Curve (连续矢量曲线绘制器)
 │    ├── 内部维护一个临时的 point_array (Vec2 数组)
 │    └── 拥有一组高级数学拟合方法：
 │         ├── .segment() ─────── 折线/极坐标步进
 │         ├── .arc() ─────────── 参数化圆弧
 │         ├── .cubic() ───────── 三次贝塞尔曲线
 │         └── .interpolation() ─ Hobby 算法点阵插值
 │
 └── Array<T> (gdstk 内部定制的仿 std::vector 高性能 C 风格动态数组)
      ├── 成员：capacity (容量), count (当前元素数), items (动态内存指针)
      └── 几乎作为所有核心数据结构（point_array, polygon_array）的底层容器
```