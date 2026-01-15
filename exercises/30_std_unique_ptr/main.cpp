#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>
/**
 * 【智能指针常用函数速查】
 * ------------------------------------------------------------
 * 函数名        |  作用说明                                    
 * ------------------------------------------------------------
 * get()        | 返回原生指针 T*（不要对其手动 delete）
 * reset()      | 释放当前对象，并指向新对象（或置空）
 * release()    | (仅 unique_ptr) 撒手不管了，返回指针需手动销毁
 * use_count()  | (仅 shared_ptr) 查看有多少人在共享这块内存
 * ptr1 = std::move(ptr2) | (针对 unique_ptr) 彻底移交所有权
 * make_unique/shared | 现代 C++ 构造智能指针的最优选方式
 * ------------------------------------------------------------
 * 注意：智能指针不需要手动调用析构函数，超出作用域（花括号）后自动工作。
 */
/**
 * 【std::unique_ptr 构造方法速查】
 * ------------------------------------------------------------
 * 1. 现代最优: auto p = std::make_unique<T>(args...);
 * 2. 默认空值: std::unique_ptr<T> p; 
 * 3. 原生指针: std::unique_ptr<T> p(new T); // 必须显式构造，不能用 = 赋值
 * 4. 所有权转移: std::unique_ptr<T> p2(std::move(p1)); // p1 变空
 * 5. 数组类型: std::unique_ptr<T[]> p(new T[10]);
 * 6. 自定义销毁: std::unique_ptr<T, D> p(ptr, d_func);
 * ------------------------------------------------------------
 * 核心警告：不要把同一个原生指针交给两个不同的 unique_ptr，否则会导致二次释放崩溃！
 */
std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;//类型重命名
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"ffr", "d"},
        {"r", "d", "d"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
