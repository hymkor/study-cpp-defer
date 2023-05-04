template <typename T>
class End {
    const T f;
public:
    End(const T &f_) : f(f_){}
    ~End(){ f(); }
};
