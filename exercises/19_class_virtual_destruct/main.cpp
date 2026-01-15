#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

/*静态字段：static 关键字修饰的成员变量或函数属于类本身，而不是属于某个具体的对象。
1唯一性：
    静态变量在程序运行期间只有一份。无论你创建了 100 个还是 0 个对象，静态变量都存在于同一个内存地址。
2不占用对象空间：
    如果你用 sizeof 查看对象大小，你会发现静态变量不计入其中。
3生命周期：
    它们在程序启动时初始化，程序结束时销毁。
4访问方式：
    可以通过类名访问：ClassName::static_var（推荐）。
    也可以通过对象访问：object.static_var（不推荐，容易误导以为是成员变量）。
5静态成员函数：
    没有 this 指针。
    只能访问类中的其他静态成员，不能访问非静态成员（因为它不知道该访问哪个对象的变量）。*/

/*虚析构函数 (Virtual Destructors)
这是继承体系中最容易导致内存泄漏的陷阱。
核心准则：如果一个类会被继承，且你会通过基类指针去操作它，那么基类的析构函数必须是 virtual。

为什么要虚析构？
    当你执行 Base *p = new Derived(); delete p; 时：
    非虚析构：编译器只看“名分”（Base*），仅调用 ~Base()。此时 Derived 对象中特有的部分（比如 new 出来的内存）不会被释放。
    虚析构：编译器会查看“真身”（Derived），先调用 ~Derived()，再调用 ~Base()。这样整个对象都能被彻底清理。*/

/**
 * STATIC & VIRTUAL DESTRUCTOR NOTES:
 * -----------------------------------------------------------------
 * 1. static 变量：
 * - 它是类的“全局变量”，所有对象共享同一个。
 * - 必须在类外进行初始化（除非是 const 整数类型）。
 * * 2. virtual 析构函数：
 * - 防止“半死不活”：确保 delete 父类指针时，子类的资源也能被释放。
 * - 只要类里有虚函数，就顺手把析构函数也写成虚的，这是 C++ 的职业操守。
 */

struct A {
    // TODO: 正确初始化静态字段
    static int num_a ;

    A() {
        ++num_a;
    }
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

int A::num_a = 0; //static成员变量需要在类外定义

struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b ;

    B() {
        ++num_b;
    }
    ~B() override {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

int B::num_b = 0; 

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;//new B会先调用基类A的构造函数（++num_a），再调用B的构造函数
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a"); 
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    //先构造父类，再构造子类
    A *ab = new B;// 派生类指针可以随意转换为基类指针 
    //new B产生的是指向一个动态分配的 B 对象的指针，类型是 B*。在 A *ab = new B; 中，右侧是 B*，再发生隐式向上转换存到 A* 里。
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    B &bb = static_cast<B&>(*ab); //此处对象确实是 B，所以静态转即可，若不确定类型应用 dynamic_cast
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象 //ab为A类指针，并且A类析构函数不为虚函数，所以未调用实际类型B类的析构函数
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
