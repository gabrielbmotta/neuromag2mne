#ifndef NEUROMAG2MNE_SHAREDPOINTER_H
#define NEUROMAG2MNE_SHAREDPOINTER_H

template<typename T>
class SharedPointer
{
public:
    SharedPointer();

    SharedPointer(T* ptr);

    SharedPointer(const SharedPointer& other);

    SharedPointer(SharedPointer&& other);

    SharedPointer& operator=(const SharedPointer& other);

    SharedPointer& operator=(SharedPointer&& other);

    ~SharedPointer();

    T* operator->() const

    T* data(); const

private:
    T* _ptr;
    unsigned int* _count;
};

#endif //NEUROMAG2MNE_SHAREDPOINTER_H