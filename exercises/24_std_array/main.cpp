#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>
/**
 * 【C++ std::array 核心总结】
 * 1. 性质：固定大小容器，内存位于栈上（Stack），性能等同于原生数组 T[N]。
 * 2. 优势：
 * - 不会退化为指针：传递给函数时仍保留类型和大小信息。
 * - 支持赋值与拷贝：可直接使用 a1 = a2 (原生数组不支持)。
 * - 迭代器支持：完美配合 STL 算法（std::sort, std::find 等）。
 * 3. 核心接口：
 * - arr[i] / arr.at(i)：访问元素（at 会进行越界检查）。
 * - arr.size()：获取元素个数 N。
 * - arr.fill(val)：将数组所有元素填充为指定值。
 * - arr.data()：返回指向底层原始数组的指针（用于 C 风格 API）。
 * 4. 初始化 (C++17)：
 * - std::array<int, 3> a = {1, 2, 3};
 * - std::array a2{1, 2}; // 自动推导类型和大小
 * 5. 注意事项：大小 N 必须是编译期常量；若需动态改变大小，请改用 std::vector。
 */
// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 5*sizeof(int) , "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.data(), ans, 20) == 0, "Fill in the correct values."); //按字节暴力比较内存内容是否相同,int memcmp( const void* lhs, const void* rhs, std::size_t count );
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value."); //int strcmp( const char* lhs, const char* rhs );
    }
    return 0;
}
