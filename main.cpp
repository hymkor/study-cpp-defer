#include <iostream>
#include "defer.h"

int main(){
    End end = [](){ std::cout << "defer code" << std::endl; };

    std::cout << "main code" << std::endl;
    return 0;
}
