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
deferClass end([](){ /* code */ });
```

と書かなくてはいけなくなる。
( 昔 VC++ で std::function で書いたときは大丈夫だった )

だが、template はどうせ `functional` の中で使われているし、この仕組み自体はどっちにしてもヘッダファイルの中に書かねばならないので、結果的に #include を減らせるこちらの方がよさそうだ。

References
----------
+ [defer っぽいもの - Qiita](https://qiita.com/SaitoAtsushi/items/afb428d0834ca4dda1e5)
+ [Go の defer っぽいものを C++ でやってみる遊び](https://gist.github.com/SaitoAtsushi/c40f4facd5754502136010fdf14228d0)
+ [scope_exitの実装 - きままにブログ](https://staryoshi.hatenablog.com/entry/2015/10/28/101841)

標準 C++ でも検討されていたが、まだ正式に入っていない模様[^StdCppDefer]

[^StdCppDefer]: https://twitter.com/shirouzu/status/1483072158758621187

+ [std::experimental::scope_exit - cppreference.com](https://en.cppreference.com/w/cpp/experimental/scope_exit)
+ [letsboost::scope_exit](http://www.kmonos.net/alang/boost/classes/scopeexit.html) (boostライブラリ)

C++ ではなく、C言語(C23) の方に先に defer が入るかもしれない

+ [A simple defer feature for C](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2895.htm) ( [新山さんのツイート](https://twitter.com/mootastic/status/1482914104549732357)より )
