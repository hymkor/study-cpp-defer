#include <iostream>
#include "defer.h"

int main(){
    // VC++ だと end = [](){...} という書き方も出来たが、
    // g++ ではコンパイルエラーになった。
    End end([](){ std::cout << "defer code" << std::endl; });

    std::cout << "main code" << std::endl;
    return 0;
}
