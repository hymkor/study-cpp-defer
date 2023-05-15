Simple `defer` for C++ like golang by destructor
================================================

main.cpp
--------

```main.cpp
#include <iostream>
#include "defer.h"

int main(){
    deferClass end = [](){ std::cout << "defer code(0)" << std::endl; };
    defer [](){ std::cout << "defer code(1)" << std::endl; };
    defer [](){ std::cout << "defer code(2)" << std::endl; };

    std::cout << "main code" << std::endl;
    return 0;
}
```

Output
------

```./a|
main code
defer code(2)
defer code(1)
defer code(0)
```


defer.h
-------

```defer.h
template <typename T>
class deferClass {
    const T f;
public:
    deferClass(const T &f_) : f(f_){}
    ~deferClass(){ f(); }
};

#define CONCATINATE_IMPLEMENT(x,y) x ## y
#define CONCATINATE(x,y) CONCATINATE_IMPLEMENT(x,y)
#define defer deferClass CONCATINATE(defer,__LINE__)=
```

余談
----

template にしなくても、`T` を `std::function<void(void)>` とすれば基本等価だが、そうすると g++ では

```cpp
deferClass end = [](){ /* code */ };
```

という書き方がエラーになり

```cpp
End end([](){ /* code */ });
```

と書かなくてはいけなくなる。
( 昔 VC++ で std::function で書いたときは大丈夫だった )

だが、template はどうせ `functional` の中で使われているし、この仕組み自体はどっちにしてもヘッダファイルの中に書かねばならないので、結果的に #include を減らせるこちらの方がよさそうだ。

References
----------
+ [defer っぽいもの - Qiita](https://qiita.com/SaitoAtsushi/items/afb428d0834ca4dda1e5)
+ [Go の defer っぽいものを C++ でやってみる遊び](https://gist.github.com/SaitoAtsushi/c40f4facd5754502136010fdf14228d0)
