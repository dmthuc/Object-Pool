#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#define private public
#include "pool.hpp"

using namespace std;
struct Foo {
    Foo(int _a, string _b)
        :a(_a), b(std::move(_b))
    {
        cout<<"constructor\n";
    }

    Foo()
        :a{},b{}
    {
        cout<<"default constructor\n";
    }
    Foo(const Foo& f)
        :a{f.a}, b{f.b}
    {
        cout<<"copy constructor\n";
    }
    Foo(Foo&& f)
        :a{f.a}, b{std::move(f.b)}
    {
        cout<<"move constructor\n"; 
    }
    
    Foo& operator=(const Foo& other)
    {
        a= other.a;
        b= other.b;
        cout<<"copy assignment";
        return *this;
    }

    Foo& operator=(Foo&& other)
    {
        a=other.a;
        b=std::move(other.b);
        cout<<"move assignment\n";
        return *this;
    }
    
    int a;
    string b;
};

void test_with_compound_type()
{
    Pool<Foo, 6> pool(1, string{"some string"});
    auto obj1 = pool.acquire();
    assert(!pool.status_[0]);
    if (nullptr != obj1.get())
        cout<<obj1->b<<'\t'<<obj1->a<<'\n';
    else
        cout<<"no obj available\n";

    auto obj2 = pool.acquire();

    assert(!pool.status_[1]);
    if (nullptr != obj2.get())
        cout<<obj2->b<<'\t'<<obj2->a<<'\n';
    else
        cout<<"no obj available\n";
}

void test_with_integral_type()
{
    Pool<int, 6> pool;
    auto obj1 = pool.acquire();
    assert(!pool.status_[0]);

    {
        auto obj2 = pool.acquire();
        assert(!pool.status_[1]);
    }
    
    assert(pool.status_[1]);
    if (nullptr != obj1.get())
        cout<<*obj1<<'\n';
    else
        cout<<"no obj available\n";
    auto obj3 = pool.acquire();
    auto obj4 = pool.acquire();
    auto obj5 = pool.acquire();
    auto obj6 = pool.acquire();
    auto obj7 = pool.acquire();
    auto obj8 = pool.acquire();
    if (nullptr != obj8.get())
        cout<<*obj8<<'\n';
    else
        cout<<"no obj available\n";
}

void constructor_test()
{
    vector<Foo> v{Foo{1,"a"}, Foo{2,"b"}};     
    Pool<Foo, 2> pool{v.begin(), v.end()}; 
    Pool<Foo, 2> pool2{Foo{1,"a"}, Foo{2,"b"}};
    for( const auto& e: pool2)
        cout<<e.b<<endl;
}


int main()
{
    test_with_integral_type();
    test_with_compound_type();
    constructor_test();
    cout<<"All test passed"<<endl;
}

