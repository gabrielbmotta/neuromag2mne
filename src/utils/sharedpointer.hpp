#ifndef NEUROMAG2MNE_SHAREDPOINTER_H
#define NEUROMAG2MNE_SHAREDPOINTER_H

template<typename T>
class SharedPointer
{
public:
    SharedPointer()
            :_ptr(NULL),_count(NULL)
    {
    }

    SharedPointer(T* ptr)
            :_ptr(NULL),_count(NULL)
    {
      if ( ptr != NULL )
      {
        _ptr = ptr;
        initCounter();
      }
    }

    SharedPointer(const SharedPointer& other)
            : _ptr(other._ptr), _count(other._count)
    {
      if( other._ptr != NULL )
      {
        incrementCount();
      }
    }

//    SharedPointer(SharedPointer&& other)
//    {
//        if (other._ptr != NULL)
//        {
//            _ptr = other._ptr;
//            _count = other._count;
//            other._ptr = NULL;
//            other._count = NULL;
//        }
//    }

    SharedPointer& operator=(const SharedPointer& other)
    {
      if( this != &other )
      {
        if ( _ptr != NULL )
        {
          decrementCount();
          deleteIfZero();
        }
        _ptr = other._ptr;
        _count = other._count;
        incrementCount();
      }
      return *this;
    }

//    SharedPointer& operator=(SharedPointer&& other)
//    {
//        if( this != &other )
//        {
//            if ( _ptr != NULL )
//            {
//                (*_count)--;
//                if ( *_count == 0 )
//                {
//                    delete _count;
//                    _count = NULL;
//                    delete _ptr;
//                    _ptr = NULL;
//                }
//            }
//            _ptr = other._ptr;
//            _count = other._count;
//            if ( _count != NULL)
//            {
//                (*_count)++;
//            }
//        }
//        return *this;
//    }

    ~SharedPointer()
    {
      if ( _ptr != NULL )
      {
        decrementCount();
        deleteIfZero();
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

    bool isConfigured() const {
      return (_ptr != NULL);
    }

    inline void initCounter()
    {
      _count = new unsigned int;
      *_count = 1;
    }

    inline void incrementCount()
    {
      if (_count != NULL)
      {
        *_count += 1;
      }
    }

    inline void decrementCount()
    {
      if (_count != NULL)
      {
        *_count -= 1;
      }
    }

    inline void deleteIfZero()
    {
      if ( *_count == 0 )
      {
        delete _count;
        _count = NULL;
        delete _ptr;
        _ptr = NULL;
      }
    }

    T* _ptr;
    unsigned int* _count;
};

#endif //NEUROMAG2MNE_SHAREDPOINTER_H
