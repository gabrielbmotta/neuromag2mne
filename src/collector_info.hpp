#ifndef COLLECTORINFO
#define COLLECTORINFO

#define COLLECTOR_ADDR      "127.0.0.1"         //collector host address
#define COLLECTOR_PORT      11122               //collector host port  
#define COLLECTOR_PASS      "homunculus122"     //collector password
#define COLLECTOR_BUFS      32768               //collector buffer size
#define COLLECTOR_CLNM      "mne_watcher"       //our client name

#define TELNET_CMD_PASS     "pass " COLLECTOR_PASS  //sends password to collector
#define TELNET_CMD_NAME     "name"  COLLECTOR_CLNM  //sends our client name to collector
#define TELNET_CMD_MONI     "moni"                  //sends command to start monitoring

#endif

