template <typename T>
class End {
    const T f;
public:
    End(const T &f_) : f(f_){}
    ~End(){ f(); }
};

#define CONCATINATE_IMPLEMENT(x,y) x ## y
#define CONCATINATE(x,y) CONCATINATE_IMPLEMENT(x,y)
#define defer End CONCATINATE(defer,__LINE__)=
