#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>
/**
 * 【std::accumulate 累积器】
 * 1. 头文件：#include <numeric>
 * 2. 作用：将序列“折叠”为一个值（求和、连乘、拼接等）。
 * 3. 关键参数：
 * - Range: 迭代器头尾。
 * - Init: 初始值（【极重要】决定了运算精度）。
 * - Op (可选): 自定义规则，默认是加法。
 * 4. 技巧：
 * - 处理浮点数时，初始值记得加 .0。
 * - 处理大数据时，注意初始值类型是否会溢出（比如用 0LL）。
 */
int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储；
    //       的张量占用的字节数
    int size = 1;
    size = std::accumulate(
        std::begin(shape),
        std::end(shape),
        sizeof(DataType),
        [](size_t acc,int dim){
            return acc*dim;
        });
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
