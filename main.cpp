#include <iostream>
#include "defer.h"

int main(){
    deferClass end = [](){ std::cout << "defer code(0)" << std::endl; };
    defer [](){ std::cout << "defer code(1)" << std::endl; };
    defer [](){ std::cout << "defer code(2)" << std::endl; };

    std::cout << "main code" << std::endl;
    return 0;
}
