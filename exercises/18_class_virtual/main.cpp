#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>
/**
 * =================================================================
 * 虚函数 (Virtual Functions) 核心要点
 * =================================================================
 * 1. 定义与目的：
 * - 在基类函数前加 'virtual'，允许派生类重写 (Override) 该函数。
 * - 核心目的：实现“动态多态”，即通过父类指针/引用调用子类的特定实现。
 * * 2. 动态绑定 (Dynamic Binding)：
 * - 只有通过【指针】或【引用】调用虚函数时，才会在运行时确定调用哪个版本。
 * - 若直接通过对象调用 (base.f())，则在编译时就确定了，不触发多态。
 * * 3. 虚析构函数 (关键！)：
 * - 只要类中有虚函数，基类的析构函数必须声明为 virtual。
 * - 否则，delete 指向子类对象的父类指针时，仅调用父类析构，导致子类内存泄漏。
 * * 4. 虚函数表 (vtable & vptr)：
 * - 编译器为每个含有虚函数的类创建一张虚函数表 (vtable)，存储函数地址。
 * - 每个对象内部含有一个隐藏指针 (vptr) 指向该表，以此实现运行时的跳转。
 * * 5. 纯虚函数与抽象类：
 * - 语法：virtual void func() = 0; 
 * - 含有纯虚函数的类叫“抽象类”，不能实例化对象，强制子类必须实现该接口。
 * * 6. override 与 final (C++11)：
 * - override: 显式标注重写，若父类无此虚函数，编译器会报错（防写错名）。
 * - final: 禁止该虚函数被子类进一步重写，或禁止类被继承。
 * =================================================================
 */

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const { //普通函数 (direct_name)：只看引用/指针的类型（Compile-time/静态绑定）
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG);
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    A &rab = b; //基类引用绑定派生类
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG);
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG);
    ASSERT(rab.direct_name() == 'A', MSG); //不是虚函数，只看引用/指针的类型
    ASSERT(rbc.direct_name() == 'B', MSG);
    ASSERT(rcd.direct_name() == 'C', MSG);

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG);
    ASSERT(rbd.virtual_name() == 'C', MSG); //B还是C? C，因为到D类中查找虚函数，发现无定义，于是去父类C中找
    ASSERT(rac.direct_name() == 'A', MSG);
    ASSERT(rbd.direct_name() == 'B', MSG);

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); //A还是C? C，同上
    ASSERT(rad.direct_name() == 'A', MSG);

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
