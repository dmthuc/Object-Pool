# Object-Pool
C++ Fast, Static and Generic Object Pool library with smart pointer  
This is static object pool library. It mean that object pool have fix number of object it manages. Client can't add more object after initialization.  
Because it is static so there's no malloc and all operator is noexcept and fast.
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
//with compound type, client can pass parameters for the constructor of containing object
Pool<Foo, 6> pool{ args1, args2}
```

