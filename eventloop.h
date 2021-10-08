#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#pragma once

#include "noncopyable.h"	
#include "currentthread.h"
#include <unistd.h>

namespace echo
{
class EventLoop: noncopyable
{
public:
	EventLoop();
	~EventLoop();

	void loop();

	void assertInLoopThread() {
		if (!isLoopThread()) {
			abortNotInLoopThread();
		}
	}
	bool isLoopThread() const { return threadId == CurrentThread::tid(); }

	static EventLoop* getEventLoopOfCurrentThread();
private:
	void abortNotInLoopThread();
private:
	bool looping;
	const pid_t threadId;
};
} // namespace echo
#endif