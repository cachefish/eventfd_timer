#include"Timer.h"
#include"Thread.h"
#include<functional>

namespace cf
{
class TimerThread
{
public:
    using TimerCallback =  std::function<void()>;
    TimerThread(int initTime,int intervalTime,TimerCallback &&cb)
    :_timer(initTime,intervalTime,std::move(cb))
    ,_thread(std::bind(&Timer::start,&_timer))
    {

    }

    void start()
    {
        _thread.start();
    }

    void stop()
    {
        _timer.stop();
        _thread.join();
    }
private:
    Timer _timer;
    Thread _thread;

};

}