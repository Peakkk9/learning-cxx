#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>
/**
 * 【C++ std::vector 核心总结】
 * 1. 性质：动态数组，内存连续，支持随机访问 (O(1))。
 * 2. 核心接口：
 * - push_back() / emplace_back()：末尾添加 (emplace 更快)。
 * - size() vs capacity()：当前元素数 vs 总共能存多少。
 * - reserve(n)：预分配空间，避免频繁扩容性能坑。
 * - at(i)：带边界检查的访问。
 * 3. 性能建议：
 * - 频繁在末尾插入：O(1) (均摊)。
 * - 频繁在头部/中间插入：O(N) (需移动大量元素)，建议改用 deque/list。
 * 4. 警告：
 * - 扩容会导致原有的迭代器、指针、引用全部失效！
 * - 只有末尾操作最快。
 */

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 3*8, "Fill in the correct value.");
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {
            vec.push_back(6);
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 3*8, "Fill in the correct value.");
            vec.pop_back();
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 3*8, "Fill in the correct value.");
        }
        {
            vec[4] = 6;
            ASSERT(vec[0] == 1, "Fill in the correct value.");
            ASSERT(vec[1] == 2, "Fill in the correct value.");
            ASSERT(vec[2] == 3, "Fill in the correct value.");
            ASSERT(vec[3] == 4, "Fill in the correct value.");
            ASSERT(vec[4] == 6, "Fill in the correct value.");
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？O(N)
            vec.insert(vec.begin()+ 1 , 1.5); //插入指定位置
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            vec.erase( vec.begin()+ 3 ); //删除指定位置
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit(); //capacity缩减成size大小
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
            vec.clear(); //删掉所有元素
            ASSERT(vec.empty(), "`vec` is empty now."); //检查是否为空
            ASSERT(vec.size() == 0, "Fill in the correct value.");
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
        }
    }
    {
        /**
         * 【std::vector 构造函数常用总结】
         * 1. 默认空：  vector<T> v;
         * 2. 初始大小：vector<T> v(n);            // n个默认值(如0)
         * 3. 大小+值： vector<T> v(n, val);       // n个val
         * 4. 列表：    vector<T> v{a, b, c...};   // 直接填入内容
         * 5. 范围拷贝：vector<T> v(it_begin, it_end); // 拷贝另一个容器区间
         * * 注意：v(10) 是10个元素，v{10} 是1个元素(值为10)。
         */
        std::vector<char> vec(48, 'z'); // TODO: 调用正确的构造函数
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        {
            auto capacity = vec.capacity();
            vec.resize(16); //强制把size减小至16
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 48, "Fill in a correct identifier.");
        }
        {
            vec.reserve(256);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
            ASSERT(vec[15] == 'z', "Fill in the correct value.");
            ASSERT(vec[16] == 'a', "Fill in the correct value.");
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}

/**
 * 【std::vector 实战方法快查】
 * * 1. 内存与大小 (Memory & Size)
 * - sizeof(vec)  : 常量值（通常24或32字节）。它只包含3个指针（指向堆内存的首、尾、容量尾），
 * 不随元素变多而变大。
 * - vec.data()   : 返回底层连续内存的首地址（等同于原生数组指针）。
 * - vec.size()   : 当前元素的个数。
 * * 2. 构造与调整 (Construction & Resizing)
 * - vector<T> v(n, val) : 创建 n 个值为 val 的元素。注意参数顺序：(个数, 值)。
 * - v.resize(n)  : 强制改变 size。若 n 变小，多余元素被销毁；若 n 变大，新增元素默认初始化。
 * - v.clear()   : 清空所有元素，size 变为 0，但 capacity 通常保持不变。
 * * 3. 增删改查 (Modifiers & Access)
 * - v.push_back(x) : 末尾添加。
 * - v.pop_back()   : 末尾弹出。
 * - v[i]           : 索引访问（不检查越界）。
 * - v.insert(it, x): 在迭代器 it 位置前插入 x，返回新元素迭代器。
 * - v.erase(it)    : 删除迭代器 it 指向的元素，返回下一个元素的迭代器。
 * * 4. 容量优化 (Capacity Control)
 * - v.capacity()   : 内部已分配的总空间（>= size）。
 * - v.reserve(n)   : 提前扩容。只改变 capacity，不改变 size。用于防止频繁重分配内存。
 * - v.shrink_to_fit(): 释放多余内存，使 capacity 等于 size。
 */