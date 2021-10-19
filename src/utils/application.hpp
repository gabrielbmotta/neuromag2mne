#ifndef APPLICATION
#define APPLICATION

class Application
{
public:
    Application();
    int run();
    void stop();
private:
    bool continueRunning;
    unsigned int uSecondsSleepTime;
};

#endif
