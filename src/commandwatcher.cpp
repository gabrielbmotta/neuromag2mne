#include "commandwatcher.hpp"

CommandWatcher::CommandWatcher()
: m_callbackCount(0)
{

}

void CommandWatcher::connect()
{

}

void CommandWatcher::disconnect()
{

}

void CommandWatcher::registerCallback(std::string str, void (*func)(std::string))
{
    m_callbackMap.insert(m_callbackCount, Callback(str, func));

    ++m_callbackCount;
}

void CommandWatcher::deleteCallback(std::string, void (*func)(std::string))
{

}

void CommandWatcher::deleteCallback(int)
{

}

void CommandWatcher::startWatching()
{

}

void CommandWatcher::stopWatching()
{

}