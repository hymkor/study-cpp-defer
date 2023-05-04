#include <functional>

class End {
    std::function<void(void)> f;
public:
    End(std::function<void(void)> f_) : f(f_){}
    ~End(){ f(); }
};
