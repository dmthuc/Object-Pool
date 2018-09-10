#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <string>
#define private public
#include "pool.hpp"

using namespace std;
struct Foo {
    int a;
    string b;
};

void test_with_compound_type()
{
    Pool<Foo, 6> pool{1, string{"some string"}};
    auto obj1 = pool.acquire();
    assert(pool.status_[0] == Is_available::no);
    if (nullptr != obj1.get())
        cout<<obj1->b<<'\t'<<obj1->a<<'\n';
    else
        cout<<"no obj available\n";
}

void test_with_integral_type()
{
    Pool<int, 6> pool;
    auto obj1 = pool.acquire();
    assert(pool.status_[0] == Is_available::no);

    {
        auto obj2 = pool.acquire();
        assert(pool.status_[1] == Is_available::no);
    }
    
    assert(pool.status_[1] == Is_available::yes);
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

int main()
{
    test_with_integral_type();
    test_with_compound_type();
    cout<<"All test passed"<<endl;
}

