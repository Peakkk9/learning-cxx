#include "../exercise.h"
#include <cstring>

// READ: 模板非类型实参 <https://zh.cppreference.com/w/cpp/language/template_parameters#%E6%A8%A1%E6%9D%BF%E9%9D%9E%E7%B1%BB%E5%9E%8B%E5%AE%9E%E5%8F%82>
/**
 * 【C++ 非类型模板参数 (NTTP) 核心总结】
 * * 1. 定义：模板参数中不以 class/typename 声明，而是具体的“值”。
 * 2. 要求：实参必须是“编译期常量表达式”（constexpr）。
 * 3. 常用类型：
 * - 整型 (int, char, bool, long 等) —— 最常用，如 std::array<int, 10>
 * - 枚举 (enum)
 * - 指针/引用 (指向全局/静态对象、函数)
 * - std::nullptr_t (C++11)
 * 4. C++20 重大更新：
 * - 支持 浮点数 (float, double)
 * - 支持 满足条件的类类型 (Literal Class)：需成员为 public 且非 mutable
 * - 支持 Lambda 表达式 (无捕获)
 * 5. 特性：
 * - auto 占位符 (C++17)：template<auto N> 自动推导参数类型。
 * - 作用：将运行期开销转为编译期计算，增强类型安全，辅助代码生成。
 * 6. 注意：字符串字面量作为参数在旧标准中受限，C++20 后支持更友好。
 */
template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for(int i=0; i<N ; ++i){
            shape[i]=shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T)); //初始化内存为0
    }
    ~Tensor() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int stride = 1;
        for (unsigned int i = 0; i < N; ++i) {
            ASSERT(indices[i] < shape[i], "Invalid index");
            // TODO: 计算 index
            index += indices[N-1-i]*stride;
            stride *= shape[N-1-i];
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
