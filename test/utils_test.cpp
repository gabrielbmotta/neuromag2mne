#include "catch.hpp"
#include "utils/thread.hpp"
#include "utils/mutex.hpp"
#include "utils/scopedpointer.hpp"
#include "utils/sharedpointer.hpp"
#include "utils/bytearray.hpp"

#include <unistd.h>

//===================================================================
// Testing threads
//===================================================================

int threadTestVal = 5;
int threadTestSleepTime = 10000;

struct ThreadTestStruct{
  int value;
  bool state;
};

void* testThread(void* input)
{
  ThreadTestStruct* ptr = static_cast<ThreadTestStruct*>(input);
  ptr->value = threadTestVal;
  while(ptr->state)
  {
    usleep(threadTestSleepTime);
  }
  ptr->value = threadTestVal + 2;
  return NULL;
};

TEST_CASE("Testing threads." , "[threads]")
{
  ThreadTestStruct a;
  a.value = threadTestVal + 1;
  a.state = true;
  Thread thread;
  thread.startThread(testThread, &a);
  usleep(threadTestSleepTime);
  REQUIRE(a.value == threadTestVal);
  thread.stopThread();
};

//===================================================================
// Testing mutexes
//===================================================================

int mutexTestVal1 = 5;
int mutexTestVal2 = 0;
int mutexTestSleepTime = 10000;

struct MutexTestStruct{
  int value;
  bool state;
  Mutex m;
};

void* testMutex(void* input)
{
  MutexTestStruct* ptr = static_cast<MutexTestStruct*>(input);

  ptr->m.lock();
  ptr->value = mutexTestVal1;

  while(ptr->state)
  {
    usleep(mutexTestSleepTime);
  }
  return NULL;
};

TEST_CASE("Testing mutex.", "[mutex]")
{
  Thread thread;
  MutexTestStruct m;

  m.value = mutexTestVal2;
  m.state = true;
  {
    m.m.lock();
    thread.startThread(testMutex, &m);
    usleep(mutexTestSleepTime);
    REQUIRE(m.value == mutexTestVal2);
    m.m.unlock();
  }
  usleep(mutexTestSleepTime);
  REQUIRE(m.value == mutexTestVal1);
  m.state = false;
  thread.stopThread();
}

//===================================================================
// Testing scoped pointers
//===================================================================

int scopedPtrTestVal = 5;

struct ScopedPointerTestObj
{
  ScopedPointerTestObj():i(scopedPtrTestVal){};
  ~ScopedPointerTestObj(){++destroyed;};

  int i;

  static int destroyed;
};
int ScopedPointerTestObj::destroyed = 0;

TEST_CASE("Testing scoped pointer", "[scoped_pointer]")
{
  {
    ScopedPointer<ScopedPointerTestObj> test;
    REQUIRE(test->i == scopedPtrTestVal);
  }
  ScopedPointer<ScopedPointerTestObj> test2;
  REQUIRE(test2->destroyed != 0);
}

//===================================================================
// Testing shared pointers
//===================================================================

int sharedPtrTestVal = 5;

struct SharedPointerTestObj
{
  SharedPointerTestObj():i(sharedPtrTestVal){};
  ~SharedPointerTestObj(){++destroyed;};

  int i;

  static int destroyed;
};
int SharedPointerTestObj::destroyed = 0;

TEST_CASE("Testing shared pointer", "[shared_pointer]")
{

  {
    SharedPointer<SharedPointerTestObj> test1;
    {
      SharedPointer<SharedPointerTestObj> test2(new SharedPointerTestObj());
      REQUIRE(test2->i == sharedPtrTestVal);
      test1 = test2;
    }
    REQUIRE(test1->destroyed == 0);
    REQUIRE(test1->i == sharedPtrTestVal);
  }
  SharedPointerTestObj test3;
  REQUIRE(test3.destroyed != 0);
}

//===================================================================
// Testing byte array
//===================================================================

int byteArrayTestVal = 5;

TEST_CASE("Testing byte array", "[byte_array]")
{
  // Are we initializing to zero/null?
  ByteArray a;
  REQUIRE(a.size() ==0);
  REQUIRE(a.data() == NULL);

  // Are we resizing properly?
  a.resize(sizeof (int));
  REQUIRE(a.size() == sizeof(int));
  REQUIRE(a.data() != NULL);
  int* value = reinterpret_cast<int*>(a.data());
  *value = byteArrayTestVal;
  REQUIRE(*(reinterpret_cast<int*>(a.data())) == byteArrayTestVal);

  // Are we copying properly? (Part 1 - Both have same values)
  ByteArray b(a);
  REQUIRE(b.size() == sizeof(int));
  REQUIRE(b.data() != NULL);
  REQUIRE(*(reinterpret_cast<int*>(b.data())) == byteArrayTestVal);

  // Are we clearing properly?
  b.clear();
  REQUIRE(b.size() == 0);
  REQUIRE(b.data() == NULL);

  // Are we copying properly? (Part 2 - We copy values, not sharing pointers)
  REQUIRE(a.size() == sizeof(int));
  REQUIRE(a.data() != NULL);
  REQUIRE(*(reinterpret_cast<int*>(a.data())) == byteArrayTestVal);

  // Are we assigning properly?
  ByteArray c;
  c = a;
  REQUIRE(c.size() == sizeof(int));
  REQUIRE(c.data() != NULL);
  REQUIRE(*(reinterpret_cast<int*>(c.data())) == byteArrayTestVal);

  // Are we copying properly? (Part 3 - We assign values, not sharing pointers)
  c.clear();
  REQUIRE(a.size() == sizeof(int));
  REQUIRE(a.data() != NULL);
  REQUIRE(*(reinterpret_cast<int*>(a.data())) == byteArrayTestVal);
}
