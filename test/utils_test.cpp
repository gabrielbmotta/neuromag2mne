#include "catch.hpp"
#include "../src/utils/thread.hpp"
#include "../src/utils/mutex.hpp"
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

struct MutexTestStruct{
  int value;
  bool state;
  Mutex m;
};

void* testMutex(void* input)
{
  MutexTestStruct* ptr = static_cast<MutexTestStruct*>(input);

  ptr->m.lock();
  ptr->value = 5;

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

  m.value = 0;
  m.state = true;
  {
    m.m.lock();
    thread.startThread(testMutex, &m);
    usleep(100);
    REQUIRE(m.value == 0);
    m.m.unlock();
  }
  usleep(100);
  REQUIRE(m.value == 5);
  m.state = false;
  thread.stopThread();
}