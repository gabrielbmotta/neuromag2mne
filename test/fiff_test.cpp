#include "catch.hpp"
#include "fiff/fifftag.hpp"
#include "fiff/fifffilewriter.hpp"
#include "utils/fileutils.hpp"

#include <cstdio>

TEST_CASE("fiff tag", "[fifftag]")
{
  fiff:fiff::Tag tag;

  //Tsting default constructor
  REQUIRE(tag.kind == 0);
  REQUIRE(tag.type == 0);
  REQUIRE(tag.size == 0);
  REQUIRE(tag.next == 0);
  REQUIRE(tag.data == NULL);

  tag.kind = 1;
  tag.type = 2;
  tag.size = 3;
  tag.next = -1;
  tag.data = new char[3];
  char* data = reinterpret_cast<char*>(tag.data);
  data[0] = 'a';
  data[1] = 'b';
  data[2] = 'c';

  // Testing copy constructor
  fiff::Tag copy = tag;
  REQUIRE(tag.kind == copy.kind);
  REQUIRE(tag.type == copy.type);
  REQUIRE(tag.size == copy.size);
  REQUIRE(tag.next == copy.next);
  REQUIRE(tag.data != copy.data);
  REQUIRE(reinterpret_cast<char*>(tag.data)[0] == reinterpret_cast<char*>(copy.data)[0]);
  REQUIRE(reinterpret_cast<char*>(tag.data)[1] == reinterpret_cast<char*>(copy.data)[1]);
  REQUIRE(reinterpret_cast<char*>(tag.data)[2] == reinterpret_cast<char*>(copy.data)[2]);

  //Testing assignment operator
  fiff::Tag copy2;
  copy2 = tag;
  REQUIRE(tag.kind == copy2.kind);
  REQUIRE(tag.type == copy2.type);
  REQUIRE(tag.size == copy2.size);
  REQUIRE(tag.next == copy2.next);
  REQUIRE(tag.data != copy2.data);
  REQUIRE(reinterpret_cast<char*>(tag.data)[0] == reinterpret_cast<char*>(copy2.data)[0]);
  REQUIRE(reinterpret_cast<char*>(tag.data)[1] == reinterpret_cast<char*>(copy2.data)[1]);
  REQUIRE(reinterpret_cast<char*>(tag.data)[2] == reinterpret_cast<char*>(copy2.data)[2]);
}

TEST_CASE("tags to file", "[tagtofile]")
{
  std::string testFilename = "test.fif";

  if(FileUtils::fileExists(testFilename))
  {
    std::remove(testFilename.c_str());
  }

  fiff::Tag tag;
  tag.kind = 3;
  tag.type = 2;
  tag.size = 1;
  tag.next = -1;
  tag.data = new char[1];
  char* data = reinterpret_cast<char*>(tag.data);
  data[0] = 'A';
  {
    fiff::FileWriter writer;
    writer.open(testFilename);
    writer.writeTag(tag);
  }

  size_t totalTagSize = sizeof (tag.kind) + sizeof (tag.type) + sizeof (tag.size) + sizeof (tag.next) + tag.size;
  ByteArray fileData = FileUtils::readFromFile(testFilename);
  REQUIRE(fileData.size() == totalTagSize);
  int32_t* dataIntPtr = reinterpret_cast<int32_t*>(fileData.data());
  REQUIRE(dataIntPtr[0] == tag.kind);
  REQUIRE(dataIntPtr[1] == tag.type);
  REQUIRE(dataIntPtr[2] == tag.size);
  REQUIRE(dataIntPtr[3] == tag.next);
  REQUIRE(fileData.data()[totalTagSize - 1] == 'A');

  std::remove(testFilename.c_str());
}
