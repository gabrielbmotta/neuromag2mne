// scopedpointer.hpp
#ifndef POINTER
#define POINTER
template<typename T>
class ScopedPointer{
public: 
    ScopedPointer():ptr(new T()){};
    ~ScopedPointer(){delete ptr;};
 
    ScopedPointer(const ScopedPointer&) = delete;
    ScopedPointer& operator=(ScopedPointer&) = delete;
    ScopedPointer& operator=(const ScopedPointer&) = delete;

    T* operator -> () const
    {
        return ptr;
    }
private:
    T* ptr;
};

#endif // POINTER
