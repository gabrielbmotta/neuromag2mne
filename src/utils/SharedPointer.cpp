#include "SharedPointer.h"


SharedPointer::SharedPointer()
        :_ptr{nullptr},_count{nullptr}
{
}

SharedPointer::SharedPointer(T* ptr)
        :_ptr{nullptr},_count{nullptr}
{
    if ( ptr != nullptr )
    {
        _count = new unsigned int;
        *_count = 1;
        _ptr = ptr;
    }
}

SharedPointer::SharedPointer(const SharedPointer& other)
        : _ptr{other._ptr}, _count{other._count}
{
    if( other._ptr != nullptr )
    {
        ++(*_count);
    }
}

SharedPointer::SharedPointer(SharedPointer&& other)
{
    if (other._ptr != nullptr)
    {
        _ptr = other._ptr;
        _count = other._count;
        other._ptr = nullptr;
        other._count = nullptr;
    }
}

SharedPointer& SharedPointer::operator=(const SharedPointer& other)
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

SharedPointer& SharedPointer::operator=(SharedPointer&& other)
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

SharedPointer::~SharedPointer()
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

T* SharedPointer::operator->()
{
    return _ptr;
}

T* SharedPointer::data()
{
    return _ptr;
}

