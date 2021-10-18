#ifndef NEUROMAG2MNE_SHAREDPOINTER_H
#define NEUROMAG2MNE_SHAREDPOINTER_H

template<typename T>
class SharedPointer
{
public:
    SharedPointer()
        :_ptr{nullptr},_count{nullptr}
    {
    }

    SharedPointer(T* ptr)
        :_ptr{nullptr},_count{nullptr}
    {
        if ( ptr != nullptr )
        {
            _count = new unsigned int;
            *_count = 1;
            _ptr = ptr;
        }
    }

    SharedPointer(const SharedPointer& other)
        : _ptr{other._ptr}, _count{other._count}
    {
        if( other._ptr != nullptr )
        {
            ++(*_count);
        }
    }

    SharedPointer(SharedPointer&& other)
    {
        if (other._ptr != nullptr)
        {
            _ptr = other._ptr;
            _count = other._count;
            other._ptr = nullptr;
            other._count = nullptr;
        }
    }

    SharedPointer& operator=(const SharedPointer& other)
    {
        if( this != &other )
        {
            if ( _ptr != nullptr )
            {
                (*_count)--;
                if ( *_count == 0 )
                {
                    delete _count;
                    _count = nullptr;
                    delete _ptr;
                    _ptr = nullptr;
                }
            }
            _ptr = other._ptr;
            _count = other._count;
            if ( _count != nullptr)
            {
                (*_count)++;
            }
        }
        return *this;
    }

    SharedPointer& operator=(SharedPointer&& other)
    {
        if( this != &other )
        {
            if ( _ptr != nullptr )
            {
                (*_count)--;
                if ( *_count == 0 )
                {
                    delete _count;
                    _count = nullptr;
                    delete _ptr;
                    _ptr = nullptr;
                }
            }
            _ptr = other._ptr;
            _count = other._count;
            if ( _count != nullptr)
            {
                (*_count)++;
            }
        }
        return *this;
    }

    ~SharedPointer()
    {
        if ( _ptr != nullptr )
        {
            (*_count)--;
            if ( *_count == 0 )
            {
                delete _count;
                _count = nullptr;
                delete _ptr;
                _ptr = nullptr;
            }
        }
    }

    T* operator->() const
    {
        return _ptr;
    }

    T* data() const
    {
        return _ptr;
    }

private:
    T* _ptr;
    unsigned int* _count;
};

#endif //NEUROMAG2MNE_SHAREDPOINTER_H