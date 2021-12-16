#include "catch.hpp"
#include "utils/thread.hpp"
#include "utils/mutex.hpp"
#include "utils/scopedpointer.hpp"
#include "utils/sharedpointer.hpp"
#include "utils/bytearray.hpp"
#include "utils/fileutils.hpp"

#include <unistd.h>

//===================================================================
// Testing threads
//===================================================================

const int threadTestVal = 5;
const int threadTestSleepTime = 10000;

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

const int mutexTestVal1 = 5;
const int mutexTestVal2 = 0;
const int mutexTestSleepTime = 10000;

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

const int scopedPtrTestVal = 5;

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

const int sharedPtrTestVal = 5;

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

const int byteArrayTestVal = 5;

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

  //Are we overloading [] correctly?
  ByteArray d;
  d.resize(4);
  d[0] = 'a';
  d[1] = 'b';
  d[2] = 'c';
  d[3] = 'd';
  REQUIRE(d.data()[0] == d[0]);
  REQUIRE(d.data()[1] == d[1]);
  REQUIRE(d.data()[2] == d[2]);
  REQUIRE(d.data()[3] == d[3]);
  REQUIRE(d[0] == 'a');
  REQUIRE(d[1] == 'b');
  REQUIRE(d[2] == 'c');
  REQUIRE(d[3] == 'd');
}

//===================================================================
// Testing file utils
//===================================================================

TEST_CASE("Testing file utils", "[fileutils]")
{
  std::string testFilePath = "test/test_files/utils_testfile1.txt";
  size_t expectedSize = 5;
  char expectedContents[] = "abcde";

  // Test file exists
  REQUIRE(FileUtils::fileExists(testFilePath));

  // Test getting file size
  REQUIRE(FileUtils::size(testFilePath) == expectedSize);

  //Test reading from file
  ByteArray a = FileUtils::readFromFile(testFilePath);
  REQUIRE(a.size() == expectedSize);
  REQUIRE(a.data() != NULL);
  char* data = reinterpret_cast<char*>(a.data());
  REQUIRE(data[0] == expectedContents[0]);
  REQUIRE(data[1] == expectedContents[1]);
  REQUIRE(data[2] == expectedContents[2]);
  REQUIRE(data[3] == expectedContents[3]);
  REQUIRE(data[4] == expectedContents[4]);

  char data2[expectedSize];
  FileUtils::fileToBuffer(testFilePath, &data2, expectedSize);
  REQUIRE(data2[0] == expectedContents[0]);
  REQUIRE(data2[1] == expectedContents[1]);
  REQUIRE(data2[2] == expectedContents[2]);
  REQUIRE(data2[3] == expectedContents[3]);
  REQUIRE(data2[4] == expectedContents[4]);
}
