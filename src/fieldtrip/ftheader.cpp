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

fieldtrip::FtHeader fieldtrip::FtHeader::simpleHeader(const BufferParameters &parameters)
{
  fieldtrip::FtHeader header;
  header.mByteArray.resize(sizeof(headerdef_t));

  header.setHeaderdef(parameters.generateHeaderdef());

  return header;
}

fieldtrip::FtHeader fieldtrip::FtHeader::extededHeader(const fieldtrip::BufferParameters &parameters,
                                                       const std::list<FtHeaderChunk *> &chunks)
{
  (void)parameters;
  (void)chunks;
  return fieldtrip::FtHeader();
}

void fieldtrip::FtHeader::appendHeaderChunk(const fieldtrip::FtHeaderChunk &chunk)
{
  (void)chunk;
  //todo: implement
}

void fieldtrip::FtHeader::setHeaderdef(const fieldtrip::headerdef_t &headerdef)
{
  if(mByteArray.size() >= sizeof(headerdef_t))
  {
    *(reinterpret_cast<headerdef_t *>(data())) = headerdef;
  }
}

size_t fieldtrip::FtHeaderChunk::size() const
{
  return mByteArray.size();
}

void* fieldtrip::FtHeaderChunk::data() const
{
  return mByteArray.data();
}

fieldtrip::FtHeaderChunk fieldtrip::FtHeaderChunk::fromFile(const std::string &filename)
{
  //todo: implement
  (void)filename;
  return fieldtrip::FtHeaderChunk();
}

// Just for later reference
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

//fieldtrip::FtHeader fieldtrip::FtHeader::neuromagHeader(const BufferParameters &parameters,
//                                                        FtHeaderChunk neuromagHeaderChunk,
//                                                        FtHeaderChunk isotrakHeaderChunk)
//{
//  (void)parameters;
//  (void)neuromagHeaderChunk;
//  (void)isotrakHeaderChunk;
//
//  return fieldtrip::FtHeader();
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
//}
