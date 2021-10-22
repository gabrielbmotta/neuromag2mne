#ifndef NEUROMAG2MNE_SHAREDPOINTER_HPP
#define NEUROMAG2MNE_SHAREDPOINTER_HPP

template<typename T>
class SharedPointer
{
public:
  SharedPointer()
      : mPtr(nullptr), mCount(nullptr)
  {
  }

  explicit SharedPointer(T* ptr)
      : mPtr(nullptr), mCount(nullptr)
  {
    if ( ptr != nullptr )
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

private:

  inline bool isConfigured() const
  {
    return (mPtr != nullptr);
  }

  inline void initCounter()
  {
    mCount = new unsigned int;
    *mCount = 1;
  }

  inline void incrementCount()
  {
    if (mCount != nullptr)
    {
      *mCount += 1;
    }
  }

  inline void decrementCount()
  {
    if (mCount != nullptr)
    {
      *mCount -= 1;
    }
  }

  inline void deleteIfZero()
  {
    if (*mCount == 0 )
    {
      delete mCount;
      mCount = nullptr;
      delete mPtr;
      mPtr = nullptr;
    }
  }

  T* mPtr;
  unsigned int* mCount;
};

#endif //NEUROMAG2MNE_SHAREDPOINTER_HPP
