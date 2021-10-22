// scopedpointer.hpp
#ifndef NEUROMAG2MNE_SCOPEDPOINTER_HPP
#define NEUROMAG2MNE_SCOPEDPOINTER_HPP

template<typename T>
class ScopedPointer{
public: 
    ScopedPointer(): mPtr(new T()){};
    ~ScopedPointer(){delete mPtr;};

    T* operator -> () const
    {
        return mPtr;
    }
    T* data() const
    {
      return mPtr;
    }
private:
    ScopedPointer(const ScopedPointer& other) { mPtr = other.mPtr;};
    ScopedPointer& operator=(ScopedPointer& other){ mPtr = other.mPtr; return *this;}
    T* mPtr;
};

#endif // NEUROMAG2MNE_SCOPEDPOINTER_HPP
