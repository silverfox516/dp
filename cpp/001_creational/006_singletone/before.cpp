#include <iostream>

class GlobalClass
{
public:
    GlobalClass(int v = 0) : m_value(v) {}
    int get_value() { return m_value; }
    void set_value(int v) { m_value = v; }

private:
    int m_value;
};

GlobalClass *global_ptr = 0;

void foo(void)
{
    if (!global_ptr)
        global_ptr = new GlobalClass;

    global_ptr->set_value(1);

    std::cout << "foo: global_ptr is " << global_ptr->get_value() << "\n";
}

void bar(void)
{
    if (!global_ptr)
        global_ptr = new GlobalClass;

    global_ptr->set_value(2);

    std::cout << "bar: global_ptr is " << global_ptr->get_value() << "\n";
}

int main()
{
    if (!global_ptr)
        global_ptr = new GlobalClass;

    std::cout << "main: global_ptr is " << global_ptr->get_value() << "\n";
    foo();
    bar();
}
