 
#include "Thread.h"
#include "Eventfd.h"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>


#include <iostream>
#include <functional>
using std::cout;
using std::endl;

void getNumber()
{
	::srand(::time(NULL));
	int number = ::rand() % 100;
	cout << ">>> subthread " << pthread_self() << "  get number " << number << endl;
}
 
int main(void)
{
	cout << "mainthread " << pthread_self() << endl;
	cf::Eventfd event(getNumber);

	cf::Thread thread(std::bind(&cf::Eventfd::start, &event));
	thread.start();

	int cnt = 10;
	while(cnt--) 
	{
		event.wakeup();
		::sleep(1);
	}

	thread.join();

	return 0;
}
