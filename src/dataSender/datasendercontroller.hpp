#ifndef NEUROMAG2MNE_DATASENDERCONTROLLER_HPP
#define NEUROMAG2MNE_DATASENDERCONTROLLER_HPP

namespace dataSender {

class DataSenderController
{
public:
  DataSenderController();
  ~DataSenderController();
  void start();
  void stop();
  void send();
private:

};

}
#endif //NEUROMAG2MNE_DATASENDERCONTROLLER_HPP
