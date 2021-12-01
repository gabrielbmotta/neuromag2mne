//
// Created by Gabriel Motta on 12/1/21.
//

#include "ftheader.hpp"

fieldtrip::Header fieldtrip::Header::simpleHeader(const BufferParameters &parameters)
{
  fieldtrip::Header header;

  header.mHeaderdata = new char[sizeof(headerdef_t)];
  headerdef_t* headerdef = static_cast<headerdef_t*>header.mHeaderdata;
  *headerdef = headerdefFromParam(parameters);

  header.mSize = sizeof(headerdef_t);

  return header;
}

fieldtrip::Header::neuromagHeader(const BufferParameters &parameters,
                                  std::string neuromagHeaderChunkFile,
                                  std::string isotrakHeaderChunkFile)
{
  bool neuromagHeaderChunk = false, isotrakHeaderChunk = false;

  std::pair<char*, size_t> neuromagByteArray = getByteArrayFromFile(neuromagHeaderPath);
  std::pair<char*, size_t> isotrakByteArray = getByteArrayFromFile(isotrakHeaderPath);


  if(neuromagByteArray.first == NULL || isotrakByteArray.first == NULL){
    std::cout << "Unable to attach files as headers. Returning simple header.\n";
    return simpleHeader(parameters);
  }
  if (neuromagByteArray.first){

  }

  size_t totalSizeOfChunks = static_cast<size_t>(neuromagByteArray.second + isotrakByteArray.second + 2 * sizeof (chunkdef_t));

  headerdef_t header = headerdefFromParam(parameters);
  header.bufsize = static_cast<int>(totalSizeOfChunks);

  size_t const totalSize = sizeof (headerdef_t) + totalSizeOfChunks;
  char* headerByteArray = new char[totalSize];

  size_t offset = 0;
  memcpy(headerByteArray + offset, &header, sizeof (headerdef_t));
  offset += sizeof (headerdef_t);

  appendHeaderChunk(headerByteArray, neuromagByteArray, 8, offset);
  appendHeaderChunk(headerByteArray, isotrakByteArray, 9, offset);
}

headerdef_t fieldtrip::Header::headerdefFromParam(const fieldtrip::BufferParameters &parameters)
{
  headerdef_t header;

  header.nchans = parameters.nChannels;
  header.fsample = parameters.sampleFrequency;
  header.data_type = parameters.dataType;

  return header;
}

static void fieldtrip::Header::appendHeaderChunk(char *headerByteArray,
                                                 std::pair<char *, size_t> &chunk,
                                                 int chunkID,
                                                 size_t &offset)
{
  chunkdef_t chunkdef;
  chunkdef.type = chunkID;
  chunkdef.size = static_cast<int>(chunk.second);

  memcpy(headerByteArray + offset, &chunkdef, sizeof(chunkdef_t));
  offset += sizeof(chunkdef_t);

  memcpy(headerByteArray + offset, chunk.first, chunk.second);
  offset += chunk.second;
}
