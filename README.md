Tny defer for C++ by destructor
===============================

main.cpp
--------

```main.cpp
#include <iostream>
#include "defer.h"

int main(){
    // VC++ だと end = [](){...} という書き方も出来たが、
    // g++ ではコンパイルエラーになった。
    End end([](){ std::cout << "defer code" << std::endl; });

    std::cout << "main code" << std::endl;
    return 0;
}
```

Output
------

```./a|
main code
defer code
```


defer.h
-------

```defer.h
#include <functional>

class End {
    std::function<void(void)> f;
public:
    End(std::function<void(void)> f_) : f(f_){}
    ~End(){ f(); }
};
```
