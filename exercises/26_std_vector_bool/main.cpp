#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>
/**
 * 【C++ 模板特化与 vector<bool>】
 * 1. 模板特化：为特定类型定制的专属模板实现。
 * - 当通用模板不满足特定类型的性能或逻辑要求时使用。
 * 2. std::vector<bool>：标准库对 bool 类型的完全特化版本。
 * - 空间优化：底层使用“位(bit)”存储，1字节可存8个bool。
 * - 副作用：不能对元素取地址，行为与常规容器略有不同。
 * 3. 语法示例：
 * template<typename T> class A {};        // 通用模板
 * template<> class A<bool> {};           // 完全特化版本
 * template<typename T> class A<T*> {};   // 偏特化版本（针对指针）
 */
// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 32, "Fill in the correct value.");
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        // WHAT: 结果是 !vec[30]，即 vec[30] 变成了 false。
        // WHY: 因为 vector<bool> 为了省空间，把 8 个 bool 挤在 1 个字节里。
        // C++ 无法对“位”直接取引用（bool&），所以它返回了一个代理类（Proxy Object）。
        // 这个代理类重载了赋值运算符，当你给 ref 赋值时，它会去修改对应字节里的那个特定的“位”。
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}

/**
 * 【std::vector<bool>::reference 代理模式】
 * 1. 现象：auto ref = vec[i]; 修改 ref 会同步修改 vec[i]。
 * 2. 原因：vector<bool> 特化后，元素以 bit 存储，无法直接返回 bool&（最小寻址单位是字节）。
 * 3. 实现：vec[i] 返回一个临时代理对象，该对象持有指向对应字节的指针及位偏移量。
 * 4. 影响：
 * - 对 ref 赋值，会触发代理类的 operator=，通过位运算修改原内存。
 * - 这就是为什么它看起来像引用，但 sizeof(ref) 并不等于 sizeof(bool)。
 * 5. 建议：在需要真正拷贝 bool 值而非引用时，建议使用 static_cast<bool>(vec[i])。
 */