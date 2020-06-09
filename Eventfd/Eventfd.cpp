 
#include "Eventfd.h"

#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <errno.h>
#include <sys/eventfd.h>
#include <iostream>
using std::cout;
using std::endl;
using namespace cf;

Eventfd::Eventfd(Callback && cb)
: _fd(createEventfd())
, _cb(std::move(cb))
, _isStarted(false)
{}

void Eventfd::start() 
{
	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	_isStarted = true;
	while(_isStarted) {
		int nready = ::poll(&pfd, 1, 5000);
		if(nready == -1 && errno == EINTR)
			continue;
		else if(nready == -1)
			exit(EXIT_FAILURE);
		else if(nready == 0) 
			cout << ">>> poll timeout!" << endl;		
		else {
			if(pfd.revents & POLLIN) {
				handleRead();	// 处理事件
				if(_cb) {// 执行任务
					_cb();
				}
			}
		}
	}
}

void Eventfd::wakeup() 
{
	uint64_t one = 1;
	int nret = ::write(_fd, &one, sizeof(uint64_t));
	if(nret != sizeof(uint64_t))
	{
		perror("write error");
	}
}

void Eventfd::handleRead()
{
	uint64_t howmany = 0;
	int nret = ::read(_fd, &howmany, sizeof(uint64_t));
	if(nret != sizeof(uint64_t))
	{
		perror("read error");
	}
}


int Eventfd::createEventfd()
{
	int fd = ::eventfd(0, 0);
	if(fd == -1)
	{
		perror(">> eventfd error");	
	}
	return fd;
}
