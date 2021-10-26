#ifndef NEUROMAG2MNE_SHAREDMEMORYMANAGER_HPP
#define NEUROMAG2MNE_SHAREDMEMORYMANAGER_HPP

#include <string>
#include "neuromagshmeminfo.hpp"
#include "sharedmemorysocket.hpp"
#include "../utils/sharedpointer.hpp"
#include "../utils/data.hpp"

namespace sharedMemory{

struct Parameters {
  Parameters();

  unsigned long int mId;
  int               mMaxData;
  int               mNumBlocks;
  int               mMaxClients;
  std::string       mClientPath;
  std::string       mServerPath;

  static Parameters neuromagDefault();

private:
  static const unsigned long int  default_NeuromagClientId;
  static const char*              default_NeuromagClientPath;
  static const char*              default_NeuromagServerPath;
  static const int                default_NeuromagMaxData;
  static const int                default_NeuromagNumBlocks;
  static const int                default_NeuromagMaxClients;
};

class Manager {
public:
  Manager();
  Manager(Parameters param);

  void connect();
  void disconnect();

  void setParameters(const Parameters &param);

  SharedPointer<Data> getData(); /*will return sharedpointer of data once added*/

private:

  void initSharedMemoryPointer();
  void confirmClientReadData(sharedMemory::Block *client);

  sharedMemory::Socket mSocket;
  sharedMemory::Block *mpSharedMemoryBlock;
  Parameters mParam;
  bool mParametersConfigured;
};

}//namespace

#endif
