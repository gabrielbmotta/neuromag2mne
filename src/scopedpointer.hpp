// scopedpointer.hpp
#ifndef POINTER
#define POINTER
template<typename T>
class ScopedPointer{
public: 
    ScopedPointer():ptr(new T()){};
    ~ScopedPointer(){delete ptr;};
 

    T* operator -> () const
    {
        return ptr;
    }
private:
    ScopedPointer(const ScopedPointer& other) {ptr = other.ptr;};
    ScopedPointer& operator=(ScopedPointer& other){ptr = other.ptr; return *this;}
    T* ptr;
};

#endif // POINTER
