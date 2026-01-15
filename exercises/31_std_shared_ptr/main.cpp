#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
/**
 * 【std::shared_ptr 核心函数查阅】
 * ------------------------------------------------------------
 * 1. 创建: 
 * auto p = std::make_shared<T>(args...); // 最优方案
 * * 2. 计数:
 * p.use_count(); // 查看当前有多少个老板 (引用计数)
 * * 3. 释放/重定向:
 * p.reset();     // 我不干了，计数-1
 * p.reset(ptr);  // 换个对象管
 * * 4. 访问:
 * p.get();       // 拿原始指针 (慎用)
 * if(p) { ... }  // 判空
 * * 5. 转换:
 * std::dynamic_pointer_cast<Derived>(base_ptr); // 转型专用
 * ------------------------------------------------------------
 * 核心警告：
 * - 避免循环引用 (A指B, B指A)，会导致内存永远无法释放。
 * - 此时需配合使用 std::weak_ptr。
 */
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>
/**
 * 【std::weak_ptr 深度总结】
 * ----------------------------------------------------------------------------
 * 1. 性质：不控制对象生命周期的“旁观者”。不增加强引用计数。
 * 2. 核心用途：
 * - 打破 shared_ptr 循环引用。
 * - 实现不增加生命周期的缓存（Cache）。
 * - 解决多线程中观察对象是否被销毁的安全问题。
 * 3. 关键函数：
 * - wp.lock()    : 【核心】尝试获取所有权。若对象还在则返回 shared_ptr，否则返回空。
 * - wp.expired() : 判断对象是否已“死”。
 * - wp.use_count(): 获取当前有多少个“老板”（shared_ptr）。
 * 4. 限制：
 * - 没有 * 或 -> 运算符，无法直接访问内容。
 * - 必须通过 lock() 提升为 shared_ptr 才能使用。
 * ----------------------------------------------------------------------------
 * 避坑：不要在构造函数中使用 shared_from_this()，除非对象已经由 shared_ptr 接管。
 */

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; //ptrs[]：这是一个数组，里面准备存放 3 个 std::shared_ptr<int>。{shared, shared, shared}：你用之前创建的那个 shared 去初始化数组里的每一个元素。

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared); //*shared只是取出了值（10），然后创建了一个全新的包裹。
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);  //当你必须接收某个东西，但你又打算直接把它扔进垃圾桶时，就用std::ignore。
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, ""); //???ptrs[0]仍为原值，不为nullptr（没有被析构）

    shared = observer.lock();//它在检查的同时直接把对象“锁住”（通过增加引用计数），保证在你使用它的这段时间里，对象绝对不会被销毁。
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock(); //观察对象已经不在，返回空指针
    ASSERT(observer.use_count() == 0, "");

    return 0;
}

/**
 * ============================================================================
 * 【智能指针选型与注意事项】
 * ============================================================================
 * 1. 优先度: unique_ptr > shared_ptr > weak_ptr。
 * 2. 避免多次构造: 
 * int* raw = new int(10);
 * shared_ptr<int> p1(raw);
 * shared_ptr<int> p2(raw); // ❌ 绝对禁止！会导致两个独立的控制块，发生二次释放。
 * * 3. 循环引用示例:
 * struct B;
 * struct A { std::shared_ptr<B> b; };
 * struct B { std::weak_ptr<A> a; }; // ✅ 使用 weak_ptr 打破循环
 * * 4. 线程安全:
 * - 引用计数的增减是原子的（线程安全）。
 * - 但对象本身的访问是不安全的，需配合 mutex。
 * * 5. 数组支持 (C++17):
 * std::shared_ptr<int[]> p(new int[10]); // C++17 后支持下标访问 p[i]
 * * 6. 常用技巧:
 * if (auto sp = wp.lock()) { // 检查并提升
 * // 对象还活着，可以使用 sp
 * }
 * ============================================================================
 */