#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>
#define private public
#include "pool.hpp"

using namespace std;

int main()
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
}

