#ifndef SHARED_PTR
#define SHARED_PTR
#include <string>
#include <vector>

template <typename T>
class SharedPtr
{
public:
    SharedPtr(T* object = nullptr):_p(std::move(object)){
        if(!count) { count = new int(1);}
    }
    SharedPtr(SharedPtr& object):_p(object._p), count(object.count){
        if(count) ++(*count);
    }
    ~SharedPtr(){
        if (count){
            (*count)--;
            if(*count == 0 && _p) {
                delete count;
                delete _p;
            }
            count = nullptr;
            _p = nullptr;
        }

    }
    T* get()const {return _p;};
    int use_count(){return count ? *count:0;};
    void reset(T* object = nullptr){
        if (count){
            (*count)--;
            if(*count == 0 && _p) {
                delete count;
                delete _p;
            }
            count = object? new int(1):nullptr ;
            _p = object;
        }
    }
    T operator*(){if(_p){
        return *_p;
        }else{
            throw std::runtime_error("Dereferencing null pointer");
        }
    };
    T* operator->(){
        if(_p){
            return _p;
        }else{
            throw std::runtime_error("Dereferencing null pointer");
        }
    };
    operator bool(){
        if(_p){
            return false;
        }else{
            return true;
        }
    }
    SharedPtr& operator=(SharedPtr& other){
        if (&other != this){
            _p = other._p;
            count = other.count;
            (*count) += 1;
        }
        return *this;
    }

private:
    T* _p;
    int* count{nullptr};
};
template <typename T, typename ...Args>
SharedPtr<T> make_shared(Args&& ... args){
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
};
#endif //SHARED_PTR