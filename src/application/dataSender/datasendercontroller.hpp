#ifndef NEUROMAG2MNE_DATASENDERCONTROLLER_HPP
#define NEUROMAG2MNE_DATASENDERCONTROLLER_HPP

#include <string>
#include <modules/fieldtrip/ftclient.hpp>

namespace dataSender {

class DataSenderController
{

  enum Mode{
    FIELDTRIP
  };
public:
  DataSenderController();
  ~DataSenderController();
  void start();
  void stop();
  void send();

  void setSendDataMode(bool sendDataMode);
  bool sendDataModeActive() const;

  void setFieldtripMode();
  void setFieldtripMode(const std::string& host, int port);
  void setFieldtripMode(const std::string& address);

private:
  bool mSendDataMode;

  //Fildtrip mode
  bool mSendToFieldTripMode;
  std::string mFieldTripAddress;
  fieldtrip::FtClient mFieldtripClient;

};

}
#endif //NEUROMAG2MNE_DATASENDERCONTROLLER_HPP
