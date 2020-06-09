#include"TimerThread.h"

#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<functional>

using std::endl;
using std::cout;

struct Task
{
    void prcess()
    {
        ::srand(::time(NULL));
        int number = ::rand()%100;
        cout<<">>number="<<number<<endl;
    }
};

int main()
{
    Task task;
    cf::TimerThread timer(3,6,std::bind(&Task::prcess,&task));
    timer.start();
    ::sleep(20);
    timer.stop();
    return 0;
}