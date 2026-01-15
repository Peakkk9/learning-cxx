#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
/**
 * =================================================================
 * 函数模板 (Function Template) 核心要点
 * =================================================================
 * 1. 目的：实现“编译期多态”，编写与类型无关的代码。
 * 2. 推导：编译器会根据实参自动推导 T 的类型（Template Argument Deduction）。
 * 3. 限制：传入的类型必须支持模板函数中的操作（如 >、+ 等），否则编译报错。
 * 4. 特化：允许为特定类型提供专门的实现。
 * 5. 位置：模板函数的【定义】通常必须放在头文件 (.h) 中，以便编译器在每个使用点进行实例化。
 * =================================================================
 */
// TODO: 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过
    ASSERT(std::abs(plus(0.1, 0.2) - 0.3) < 1e-9, "How to make this pass?");

    return 0;
}
