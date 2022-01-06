#include "catch.hpp"
#include "application/modules/fieldtrip/ftclient.hpp"
#include "application/modules/fieldtrip/ftheader.hpp"
#include "application/modules/fieldtrip/ftdata.hpp"
#include "application/modules/fieldtrip/ftmessage.hpp"

//===================================================================
// Testing struct sizes
//===================================================================
const size_t expectedSizeofMessageDef = 8;
const size_t expectedSizeofHeaderDef = 24;
const size_t expectedSizeofDataDef = 16;
const size_t expectedSizeofChunkDef = 8;

TEST_CASE("fieldtrip struct sizes", "[ftstructs]")
{
    REQUIRE(sizeof(fieldtrip::messagedef_t) == expectedSizeofMessageDef);
    REQUIRE(sizeof(fieldtrip::headerdef_t) == expectedSizeofHeaderDef);
    REQUIRE(sizeof(fieldtrip::datadef_t) == expectedSizeofDataDef);
    REQUIRE(sizeof(fieldtrip::chunkdef_t) == expectedSizeofChunkDef);
}

//===================================================================
// Testing header formatting
//===================================================================

const int test_numChannels = 10, test_dataType = 1;
const float test_sampleFreq = 1000.0f;

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

  // Are we formatting the message correctly in memory?
  fieldtrip::FtHeader header1 = fieldtrip::FtHeader::simpleHeader(fieldtrip::BufferParameters(test_numChannels,test_sampleFreq,test_dataType));
  fieldtrip::FtMessage msg2 = fieldtrip::FtMessage::headerMessage(header1);
  REQUIRE(msg2.size() == header1.size() + sizeof(fieldtrip::messagedef_t));
  REQUIRE(msg2.data() != NULL);
  fieldtrip::messagedef_t* msgdef = reinterpret_cast<fieldtrip::messagedef_t*>(msg2.data());
  REQUIRE(msgdef->bufsize == header1.size());
  REQUIRE(msgdef->version == 1);
  REQUIRE(msgdef->command == PUT_HDR);
  fieldtrip::headerdef_t* headerdef = reinterpret_cast<fieldtrip::headerdef_t*>(reinterpret_cast<char*>(msg2.data()) + sizeof(fieldtrip::messagedef_t));
  REQUIRE(headerdef->bufsize == 0);
  REQUIRE(headerdef->nchans == test_numChannels);
  REQUIRE(headerdef->fsample == test_sampleFreq);
}
