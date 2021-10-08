#include "eventloop.h"

#include <iostream>

#include <cassert>
#include <stdio.h>
#include <poll.h>

using namespace echo;

namespace 
{
    __thread EventLoop* t_loopInThisThread = 0;
} // namespace

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
  return t_loopInThisThread;
}

EventLoop::EventLoop()
    : looping(false),
    threadId(CurrentThread::tid())
{
	if (t_loopInThisThread) {
        std::cout << "Another EventLoop " << t_loopInThisThread \
              << " exists in this thread " << threadId \
              << std::endl;
    } else {
        t_loopInThisThread = this;
    }
}
	
EventLoop::~EventLoop()
{
    assert(!looping);
    t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
	assert(!looping);
    assertInLoopThread();

    looping = true;
    ::poll(NULL, 0, 5*1000);

    std::cout << "EventLoop stop looping" << std::endl;
    looping = false;
}

void EventLoop::abortNotInLoopThread()
{
	std::cout << "EventLoop::abortNotInLoopThread - EventLoop " << std::endl;
}