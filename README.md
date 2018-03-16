# Object-Pool
C++ Fast, Static and Generic Object Pool library with smart pointer

- Contact: minhthucdao1@gmail.com
- Usage: just include pool.hpp into your source code
```
/*your cpp file*/
#include "pool.hpp"
Pool<int, 6> pool;
auto obj1 = pool.acquire();
if (nullptr != obj.get())
    dosomething(*obj);
else
    throw("no object in pool available");
```
