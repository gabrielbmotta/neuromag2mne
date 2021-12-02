//
// Created by Gabriel Motta on 12/1/21.
//

#include "ftheader.hpp"

size_t fieldtrip::FtHeader::size() const
{
  return mByteArray.size();
}

void* fieldtrip::FtHeader::data() const
{
  return mByteArray.data();
}

size_t fieldtrip::FtHeaderChunk::size() const
{
  return mByteArray.size();
}

void* fieldtrip::FtHeaderChunk::data() const
{
  return mByteArray.data();
}

fieldtrip::FtHeader fieldtrip::FtHeaderFormater::simpleHeader(const BufferParameters &parameters)
{
  fieldtrip::FtHeader header;

  header.mByteArray.resize(sizeof(headerdef_t));
  headerdef_t* headerdef = static_cast<headerdef_t*>(header.data());
  *headerdef = headerdefFromParam(parameters);

  return header;
}

fieldtrip::FtHeader fieldtrip::FtHeaderFormater::neuromagHeader(const BufferParameters &parameters,
                                                        FtHeaderChunk neuromagHeaderChunk,
                                                        FtHeaderChunk isotrakHeaderChunk)
{
  (void)parameters;
  (void)neuromagHeaderChunk;
  (void)isotrakHeaderChunk;

  return fieldtrip::FtHeader();
//  //todo: this 'works' for now, but
//  //      there needs to be a better abstraction
//  //      for adding things to headers cleanly
//
//  std::pair<char*, size_t> neuromagByteArray = getByteArrayFromFile(neuromagHeaderPath);
//  std::pair<char*, size_t> isotrakByteArray = getByteArrayFromFile(isotrakHeaderPath);
//
//  if(neuromagByteArray.first == NULL || isotrakByteArray.first == NULL){
//    std::cout << "Unable to attach files as headers. Returning simple header.\n";
//    return simpleHeader(parameters);
//  }
//
//  size_t totalSizeOfChunks = static_cast<size_t>(neuromagByteArray.second + isotrakByteArray.second + 2 * sizeof (chunkdef_t));
//
//  headerdef_t header = headerdefFromParam(parameters);
//  header.bufsize = static_cast<int>(totalSizeOfChunks);
//
//  fieldtrip::FtHeader header;
//  header.rezise(sizeof (headerdef_t) + totalSizeOfChunks);
//
//  size_t offset = 0;
//  memcpy(headerByteArray + offset, &header, sizeof (headerdef_t));
//  offset += sizeof (headerdef_t);
//
//  appendHeaderChunk(headerByteArray, neuromagByteArray, 8, offset);
//  appendHeaderChunk(headerByteArray, isotrakByteArray, 9, offset);
}

fieldtrip::FtHeader fieldtrip::FtHeaderFormater::extededHeader(const BufferParameters &parameters, const std::list<FtHeaderChunk *> &chunks)
{
  (void)parameters;
  (void)chunks;
  return FtHeader();
}

headerdef_t fieldtrip::FtHeaderFormater::headerdefFromParam(const fieldtrip::BufferParameters &parameters)
{
  headerdef_t header;

  header.nchans = parameters.nChannels;
  header.fsample = parameters.sampleFrequency;
  header.data_type = parameters.dataType;

  return header;
}

//static void fieldtrip::FtHeaderFormater::appendHeaderChunk(char *headerByteArray,
//                                                   std::pair<char *, size_t> &chunk,
//                                                   int chunkID,
//                                                   size_t &offset)
//{
//  chunkdef_t chunkdef;
//  chunkdef.type = chunkID;
//  chunkdef.mSize = static_cast<int>(chunk.second);
//
//  memcpy(headerByteArray + offset, &chunkdef, sizeof(chunkdef_t));
//  offset += sizeof(chunkdef_t);
//
//  memcpy(headerByteArray + offset, chunk.first, chunk.second);
//  offset += chunk.second;
//}

void fieldtrip::FtHeaderFormater::appendHeaderChunk(const FtHeader& header,
                                                    const FtHeaderChunk& chunk)
{
 //todo: turn the function above into this one, but right this time.
  (void)header;
  (void)chunk;
}

//==============================================================================
// Not to be used
//==============================================================================

/*
Set to private - not intended to be used and '= delete' is c++11.
*/
fieldtrip::FtHeaderFormater::FtHeaderFormater()
{

}
