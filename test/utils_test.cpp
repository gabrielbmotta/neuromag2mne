#include "catch.hpp"
#include "../src/utils/thread.hpp"
#include "../src/utils/mutex.hpp"
#include "../src/utils/scopedpointer.hpp"
#include "../src/utils/sharedpointer.hpp"

#include <unistd.h>

//===================================================================
// Testing threads
//===================================================================

struct ThreadTestStruct{
  int value;
  bool state;
};

void* testThread(void* input)
{
  ThreadTestStruct* ptr = static_cast<ThreadTestStruct*>(input);
  ptr->value = 5;
  while(ptr->state)
  {
    usleep(100);
  }
  ptr->value = 10;
  return NULL;
};

TEST_CASE("Testing threads." , "[threads]")
{
  ThreadTestStruct a;
  a.value = 0;
  a.state = true;
  Thread thread;
  thread.startThread(testThread, &a);
  usleep(100);
  REQUIRE(a.value == 5);
  thread.stopThread();
};

//===================================================================
// Testing mutexes
//===================================================================

int mutexTestVal1 = 5;
int mutexTestVal2 = 0;

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
    usleep(100);
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
    usleep(100);
    REQUIRE(m.value == mutexTestVal2);
    m.m.unlock();
  }
  usleep(100);
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
