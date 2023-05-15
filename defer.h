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
