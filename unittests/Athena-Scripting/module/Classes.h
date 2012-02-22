#ifndef _CLASSES_H_
#define _CLASSES_H_

class Base
{
public:
    Base(int a_)
    : a(a_)
    {
    }


    // Methods
    virtual void f()
    {
        a *= 2;
    }

    void g()
    {
        a = 100;
    }


    // Attributes
    int a;
};


class Derived: public Base
{
public:
    Derived(int a_, int b_)
    : Base(a_), b(b_)
    {
    }


    // Methods
    virtual void f()
    {
        a *= 3;
        b *= 2;
    }

    void h()
    {
        b = 200;
    }


    // Attributes
    int b;
};

#endif
