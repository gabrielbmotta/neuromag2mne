
#include "datasendercontroller.hpp"
#include <stdlib.h>


dataSender::DataSenderController::DataSenderController()
{

}

dataSender::DataSenderController::~DataSenderController()
{

}

void dataSender::DataSenderController::start()
{


}

void dataSender::DataSenderController::stop()
{

}

void dataSender::DataSenderController::send()
{

}

void dataSender::DataSenderController::setSendDataMode(bool sendDataMode)
{
  mSendDataMode = sendDataMode;
}

bool dataSender::DataSenderController::sendDataModeActive() const
{
  return mSendDataMode;
}

void dataSender::DataSenderController::setFieldtripMode()
{
  setFieldtripMode("127.0.0.1", 1972);
}

void dataSender::DataSenderController::setFieldtripMode(const std::string& host, int port)
{
  mFieldtripClient.connect(host, static_cast<unsigned short>(port));
  if(mFieldtripClient.isConnected())
  {
    mSendToFieldTripMode = true;
    mSendDataMode = true;
  }
}

void dataSender::DataSenderController::setFieldtripMode(const std::string& address)
{
  if(!address.empty())
  {
    size_t pos = address.find(':');
    if(pos != std::string::npos)
    {
      setFieldtripMode(address.substr(0, pos), atoi(address.substr(pos + 1).c_str()));
    }
    else
    {
      setFieldtripMode(address, 1972);
    }
  } else {
    setFieldtripMode();
  }
}
