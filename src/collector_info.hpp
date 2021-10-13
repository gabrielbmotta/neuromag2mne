#ifndef COLLECTORINFO
#define COLLECTORINFO

#define COLLECTOR_ADDR      "127.0.0.1"         //collector host address
#define COLLECTOR_PORT      11122               //collector host port  
#define COLLECTOR_PASS      "homunculus122"     //collector password
#define COLLECTOR_BUFS      32768               //collector buffer size
#define COLLECTOR_CLNM      "mne_watcher"       //our client name

#define RETURN "\r\n" //runs telnet command

#define TELNET_CMD_PASS     "pass "   COLLECTOR_PASS   RETURN     //sends password to collector
#define TELNET_CMD_NAME     "name "   COLLECTOR_CLNM   RETURN     //sends our client name to collector
#define TELNET_CMD_MONI     "moni on"                  RETURN     //sends command to start monitoring

#endif

