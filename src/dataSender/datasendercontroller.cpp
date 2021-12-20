
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

bool dataSender::DataSenderController::sendDataModeActive()
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
  size_t pos = address.find(':');
  if(pos != std::string::npos)
  {
    std::string host = address.substr(0, pos);
    std::string port = address.substr(pos + 1);
    setFieldtripMode(host, atoi(port.c_str()));
  }
}
