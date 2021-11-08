#ifndef NEUROMAG2MNE_SHAREDPOINTER_HPP
#define NEUROMAG2MNE_SHAREDPOINTER_HPP

#include "utils_global.hpp"

template<typename T>
class SharedPointer
{
public:
  SharedPointer()
      : mPtr(NULL), mCount(NULL)
  {
  }

  explicit SharedPointer(T* ptr)
      : mPtr(NULL), mCount(NULL)
  {
    if ( ptr != NULL )
    {
      mPtr = ptr;
      initCounter();
    }
  }

  SharedPointer(const SharedPointer& other)
      : mPtr(other.mPtr), mCount(other.mCount)
  {
    if( other.isConfigured() )
    {
      incrementCount();
    }
  }

  SharedPointer& operator=(const SharedPointer& other)
  {
    if( this != &other )
    {
      if ( isConfigured() )
      {
        decrementCount();
        deleteIfZero();
      }
      if ( other.isConfigured() )
      {
        mPtr = other.mPtr;
        mCount = other.mCount;
        incrementCount();
      } else {
        mPtr = other.mPtr;
        mCount = other.mCount;
      }
    }
    return *this;
  }

  ~SharedPointer()
  {
    if ( isConfigured() )
    {
      decrementCount();
      deleteIfZero();
    }
  }

  T* operator->() const
  {
    return mPtr;
  }

  T* data() const
  {
    return mPtr;
  }

private:

  inline bool isConfigured() const
  {
    return (mPtr != NULL);
  }

  inline void initCounter()
  {
    mCount = new unsigned int;
    *mCount = 1;
  }

  inline void incrementCount()
  {
    if (mCount != NULL)
    {
      *mCount += 1;
    }
  }

  inline void decrementCount()
  {
    if (mCount != NULL)
    {
      *mCount -= 1;
    }
  }

  inline void deleteIfZero()
  {
    if (*mCount == 0 )
    {
      delete mCount;
      mCount = NULL;
      delete mPtr;
      mPtr = NULL;
    }
  }

  T* mPtr;
  unsigned int* mCount;
};

#endif //NEUROMAG2MNE_SHAREDPOINTER_HPP
