#ifndef _TIMER_H__
#define _TIMER_H__

#include<functional>

namespace cf
{
class Timer
{
public:
    using TimerCallback = std::function<void()>;

    Timer(int ,int,TimerCallback&&cb);

    void start();
    void stop();
private:
    void handleRead();
    
    int createTimerfd();
    void setTimerfd(int initTime,int intervalTime);
private:
    int _fd;
    int _initTime;
    int _intervalTime;
    TimerCallback _cb;
    bool _isStarted; 
};

}

#endif