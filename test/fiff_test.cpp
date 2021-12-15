#include "catch.hpp"
#include "fiff/fifftag.hpp"

TEST_CASE("fiff tag", "[fifftag]")
{
  fiff:fiff::Tag tag;
  tag.kind = 1;
  tag.type = 2;
  tag.size = 3;
  tag.next = -1;
  tag.data = new char[3];
  reinterpret_cast<char*>(tag.data)[0] = 'a';
  reinterpret_cast<char*>(tag.data)[1] = 'b';
  reinterpret_cast<char*>(tag.data)[2] = 'c';

  fiff::Tag copy = tag;
  REQUIRE(tag.kind == copy.kind);
  REQUIRE(tag.type == copy.type);
  REQUIRE(tag.size == copy.size);
  REQUIRE(tag.next == copy.next);
  REQUIRE(tag.data != copy.data);
  REQUIRE(reinterpret_cast<char*>(tag.data)[0] == reinterpret_cast<char*>(copy.data)[0]);
  REQUIRE(reinterpret_cast<char*>(tag.data)[1] == reinterpret_cast<char*>(copy.data)[1]);
  REQUIRE(reinterpret_cast<char*>(tag.data)[2] == reinterpret_cast<char*>(copy.data)[2]);
}