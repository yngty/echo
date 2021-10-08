#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#pragma once
	
class EventLoop  
{
public:
	EventLoop();
	~EventLoop();

	void loop();

private:
	bool looping;
	const pid_t threadId;
};
#endif