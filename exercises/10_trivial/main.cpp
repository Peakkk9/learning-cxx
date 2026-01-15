#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>
// 平凡类型：1没有自定义构造/析构函数：必须使用编译器生成的默认版本（或显式写 = default）。
// 2没有虚函数或虚基类：不能有 virtual 关键字。
// 3成员也必须是平凡的：结构体里的所有成员变量也得满足上述条件。

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    if(cache.cached<2){
        cache.cache[0]=0;
        cache.cache[1]=1;
        cache.cached=2;
    } 
    //仅使用cache.cached < 16为一次性把斐波那契数列算完，也可以，但不适用于数列特别长的情况
    //cache.cached <= i && cache.cached < 16，为用户要求到哪算到哪，下次从这个序号的下一个值开始算（因为cached存储下来了已算出的数列个数）
    for (; cache.cached <= i && cache.cached < 16 ; ++cache.cached) {
            cache.cache[cache.cached] = cache.cache[cache.cached - 1] + cache.cache[cache.cached - 2];
        }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib{};
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
