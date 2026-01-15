#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s;
    auto world = "world"; //双引号字符数组，只读
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), const char *>), "Fill in the missing type.");
    // TODO: 将 `?` 替换为正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    return 0;
}

/**
 * ============================================================================
 * 【C++ std::string 全方位实战手册】
 * ============================================================================
 * * 1. 基础定义与初始化
 * ----------------------------------------------------------------------------
 * - std::string s;                  // 默认构造，空字符串
 * - std::string s = "hello";        // 从 C 风格字符串（const char*）构造
 * - std::string s(5, 'a');          // 构造为 "aaaaa"
 * - auto s = "hello"s;              // C++14 字面量后缀，直接得到 string 对象
 * // (需声明 using namespace std::string_literals;)
 * * 2. 内存管理与性能 (SSO & Capacity)
 * ----------------------------------------------------------------------------
 * - size() / length() : 返回字符个数（不计末尾 \0）。
 * - capacity()        : 内部已分配的总空间。
 * - empty()           : 检查是否为空，优于 size() == 0。
 * - reserve(n)        : 【重要】预分配空间。建议在大量拼接前调用，避免频繁扩容导致的拷贝。
 * - shrink_to_fit()   : 释放多余的 capacity 内存。
 * - SSO (小字符串优化) : 短字符串（通常 <16 字节）直接存入栈上的对象内部，不分配堆内存。
 * * 3. 元素访问 (Access)
 * ----------------------------------------------------------------------------
 * - s[i]              : 快速下标访问，不检查越界。
 * - s.at(i)           : 带越界检查的访问，失败抛出 std::out_of_range。
 * - s.front() / back(): 获取首尾字符。
 * - s.c_str()         : 【重要】返回指向底层连续内存的 const char*，兼容 C 接口。
 * - s.data()          : C++11 起等同于 c_str()；C++17 起返回非 const 指针。
 * * 4. 修改操作 (Modifiers)
 * ----------------------------------------------------------------------------
 * - s += "text";      : 拼接字符串或字符（最高效的拼接方式）。
 * - s.append("text"); : 等同于 +=。
 * - s.push_back('c'); : 在末尾追加单个字符。
 * - s.insert(pos, str): 在 pos 位置插入子串。
 * - s.erase(pos, len) : 从 pos 开始删除 len 个字符。
 * - s.replace(pos, len, "new") : 替换指定范围内的子串。
 * - s.clear();        : 清空内容，但通常 capacity 不会减小。
 * * 5. 查找与子串 (Search & Substr)
 * ----------------------------------------------------------------------------
 * - s.find("sub")     : 返回子串首次出现的索引，找不到返回 std::string::npos。
 * - s.rfind("sub")    : 从后往前查找。
 * - s.substr(pos, len): 【慎用】截取子串。会产生新 string 对象并拷贝内容，开销大。
 * * 6. 现代 C++ 增强功能
 * ----------------------------------------------------------------------------
 * - decltype("str"s)  : 推导结果为 std::string。
 * - decltype("str")   : 推导结果为 const char*。
 * - std::is_same_v<T1, T2> : 编译期判断类型是否一致。
 * - std::string_view  : (C++17) 零拷贝的字符串视图。
 * 作为函数参数时：void func(std::string_view sv);
 * 它不拥有内存，仅持有指针+长度，极大地优化了只读操作。
 * * 7. 性能最佳实践 (Performance Tips)
 * ----------------------------------------------------------------------------
 * - 传参：优先使用 const std::string& 或 std::string_view。
 * - 拼接：循环内拼接请务必先 reserve()。
 * - 查找：尽量使用 find 族函数而非手写循环。
 * - 转换：使用 std::to_string(num) 将数值转为 string。
 * * ============================================================================
 */