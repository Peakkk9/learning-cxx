#include "../exercise.h"
#include <map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>
/**
 * 【C++ Map 核心对比与选型】
 * -----------------------------------------------------------
 * 特性          | std::map                | std::unordered_map
 * -----------------------------------------------------------
 * 底层实现       | 红黑树 (Tree)           | 哈希表 (Hash Table)
 * 排序           | 按 Key 有序             | 无序
 * 查找效率       | O(log N) - 稳定         | O(1) - 平均极快
 * Key 要求       | 需支持 < 运算            | 需支持 hash 和 ==
 * 场景           | 需要有序/范围查找        | 绝大多数普通查找场景
 * -----------------------------------------------------------
 * 常用技巧:
 * 1. 查找是否存在: if (m.count(key)) 或 if (m.find(key) != m.end())
 * 2. 遍历: for (auto const& [k, v] : m) { ... }
 * 3. 慎用 m[key]: 它会副作用插入元素，只读场景请用 m.at(key)。
 */

template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // TODO: 实现函数
    if(map.find(key)!= map.end()){
        return true;
    }else{
        return false;
    }
}

template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // TODO: 实现函数
    map[key]=value;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    set(secrets, "hello"s, "world"s);
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" shoud be in `secrets`");
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" shoud not be in `secrets`");

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    return 0;
}
