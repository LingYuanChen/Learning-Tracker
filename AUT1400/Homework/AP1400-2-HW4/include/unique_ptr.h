#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <string>
#include <vector>
template <typename T>

class UniquePtr
{
public:
    UniquePtr(T* object = nullptr):_p(std::move(object)){};
    UniquePtr(UniquePtr& other): _p(other._p) {}
    ~UniquePtr(){ if(!_p) { delete _p; _p = nullptr; } }
    T* get() const {return _p;};
    T* release(){
        T* tmp = _p;
        _p = nullptr;
        return tmp;
    }
    T operator*(){return *_p;};
    T* operator->(){return _p;};
    operator bool(){if(_p){return true;} else {return false;}}
    void reset(T* object = nullptr){_p = object;}


private:
    T* _p;
};

template <class T, typename... Args>
UniquePtr<T> make_unique(Args&& ... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

// T* UniquePtr::make_unique(T* object){
//     return new object;
// };










#endif //UNIQUE_PTR