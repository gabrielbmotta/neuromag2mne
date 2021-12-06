#include "catch.hpp"
#include "fieldtrip/ftclient.hpp"
#include "fieldtrip/ftheader.hpp"
#include "fieldtrip/ftdata.hpp"
#include "fieldtrip/ftmessage.hpp"

//===================================================================
// Testing struct sizes
//===================================================================
size_t expectedSizeofMessageDef = 8;
size_t expectedSizeofHeaderDef = 24;
size_t expectedSizeofDataDef = 16;

TEST_CASE("fieldtrip struct sizes", "[ftstructs]")
{
    REQUIRE(sizeof(fieldtrip::messagedef_t) == expectedSizeofMessageDef);
    REQUIRE(sizeof(fieldtrip::headerdef_t) == expectedSizeofHeaderDef);
    REQUIRE(sizeof(fieldtrip::datadef_t) == expectedSizeofDataDef);
}

//===================================================================
// Testing header formatting
//===================================================================

int test_numChannels = 10, test_dataType = 1;
float test_sampleFreq = 1000.0f;

TEST_CASE("fieldtrip header formatting" "[ftmsg]")
{
  // Are we initializing to zero/null?
  fieldtrip::FtHeader header1;
  REQUIRE(header1.size() == 0);
  REQUIRE(header1.data() == NULL);

  // Are we formatting the header correctly in memory?
  fieldtrip::FtHeader header2 = fieldtrip::FtHeader::simpleHeader(fieldtrip::BufferParameters(test_numChannels,test_sampleFreq,test_dataType));
  REQUIRE(*reinterpret_cast<int32_t*>(header2.data()) == test_numChannels);
  REQUIRE(*(reinterpret_cast<float*>(header2.data()) + 3) == test_sampleFreq);
  REQUIRE(*(reinterpret_cast<int32_t*>(header2.data()) + 4) == test_dataType);

  // Are we formatting the header chunks correctly in memory?
  fieldtrip::FtHeaderChunk headerChunk1;
  REQUIRE(headerChunk1.size() == 0);
  REQUIRE(headerChunk1.data() == NULL);

  fieldtrip::FtHeaderChunk headerChunk2 = fieldtrip::FtHeaderChunk::fromFile("test/test_files/ftbuffer_testfile1.txt", 50);
  fieldtrip::chunkdef_t* chunkdef = reinterpret_cast<fieldtrip::chunkdef_t*>(headerChunk2.data());
  REQUIRE(headerChunk2.size() == 3 + sizeof (fieldtrip::chunkdef_t));
  REQUIRE(headerChunk2.data() != NULL);
  REQUIRE(chunkdef->type == 50);
  REQUIRE(chunkdef->size == 3);

  // Are we formatting the extended header correctly?
  std::list<fieldtrip::FtHeaderChunk*> chunkList;
  chunkList.push_back(&headerChunk2);
  fieldtrip::FtHeader header3 = fieldtrip::FtHeader::extendedHeader(fieldtrip::BufferParameters(test_numChannels,test_sampleFreq,test_dataType),
                                                                    chunkList);

  REQUIRE(header3.size() == headerChunk2.size() + sizeof(fieldtrip::headerdef_t));
  fieldtrip::headerdef_t* headerdef = reinterpret_cast<fieldtrip::headerdef_t*>(header3.data());
  REQUIRE(headerdef->bufsize == headerChunk2.size());
}

//===================================================================
// Testing data formatting
//===================================================================

TEST_CASE("fieldtrip data formatting" "[ftmsg]")
{

}

//===================================================================
// Testing message formatting
//===================================================================

TEST_CASE("fieldtrip message formatting" "[ftmsg]")
{
  // Are we initializing to zero/null?
  fieldtrip::FtMessage msg1;
  REQUIRE(msg1.size() == 0);
  REQUIRE(msg1.data() == NULL);

  fieldtrip::FtHeader header1 = fieldtrip::FtHeader::simpleHeader(fieldtrip::BufferParameters(test_numChannels,test_sampleFreq,test_dataType));
  fieldtrip::FtMessage msg2 = fieldtrip::FtMessage::headerMessage(header1);

}

