//
// Created by Gabriel Motta on 12/1/21.
//

#include "ftheader.hpp"
#include "utils/fileutils.hpp"

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

fieldtrip::FtHeader fieldtrip::FtHeader::extendedHeader(const fieldtrip::BufferParameters &parameters,
                                                        const std::list<FtHeaderChunk *> &chunks)
{
  fieldtrip::FtHeader header;
  size_t totalSize = sizeof(headerdef_t) + FtHeaderChunk::totalSize(chunks);

  header.mByteArray.resize(totalSize);
  header.setHeaderdef(parameters.generateHeaderdef());

  std::list<FtHeaderChunk *>::const_iterator it;
  for(it = chunks.begin(); it != chunks.end(); it++)
  {
    header.appendHeaderChunk(**it);
  }

  return header;
}

fieldtrip::FtHeader fieldtrip::FtHeader::extendedHeader(const fieldtrip::BufferParameters &parameters,
                                                        fieldtrip::FtHeaderChunk* chunks, ...)
{
  std::list<FtHeaderChunk *> chunkList;
  va_list args;
  va_start(args, chunks);
  for(FtHeaderChunk *chunk = chunks; chunk != nullptr; chunk = va_arg(args, FtHeaderChunk *))
  {
    chunkList.push_back(chunk);
  }
  va_end(args);

  return extendedHeader(parameters, chunkList);
}

void fieldtrip::FtHeader::appendHeaderChunk(const fieldtrip::FtHeaderChunk &chunk)
{
  headerdef_t* headerdef = reinterpret_cast<headerdef_t*>(mByteArray.data());
  size_t offset = static_cast<size_t>(headerdef->bufsize);

  memcpy(mByteArray.data() + offset, chunk.data(), chunk.size());
  headerdef->bufsize += static_cast<int32_t>(chunk.size());
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

fieldtrip::FtHeaderChunk fieldtrip::FtHeaderChunk::fromFile(const std::string &filename, int chunkId)
{
  size_t size = FileUtils::size(filename);
  if(size < 1)
  {
    return FtHeaderChunk();
  }

  FtHeaderChunk chunk;
  chunk.mByteArray.resize(sizeof(chunkdef_t) + size);
  chunk.setChunkDef(chunkdef_t(chunkId, static_cast<int32_t>(size)));
  chunk.setChunkContents(FileUtils::getByteArrayFromFile(filename).data(), size);

  return chunk;
}

size_t fieldtrip::FtHeaderChunk::totalSize(const std::list<FtHeaderChunk *>& chunks)
{
  size_t totalSize = 0;
  std::list<FtHeaderChunk *>::const_iterator it;
  for(it = chunks.begin(); it != chunks.end(); it++)
  {
    totalSize += (*it)->size();
  }
  return totalSize;
}

void fieldtrip::FtHeaderChunk::setChunkDef(const fieldtrip::chunkdef_t &chunkdef)
{
  if(mByteArray.size() >= sizeof(chunkdef_t))
  {
    *(reinterpret_cast<chunkdef_t *>(data())) = chunkdef;
  }
}

void fieldtrip::FtHeaderChunk::setChunkContents(const void *data, size_t size)
{
  memcpy(mByteArray.data() + sizeof(chunkdef_t), data, size);
}
