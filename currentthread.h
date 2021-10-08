#ifndef CURRENTTHREAD_H
#define CURRENTTHREAD_H
#pragma once

#include <unistd.h>

namespace echo
{
	namespace CurrentThread
	{
		// internal
		extern __thread int t_cachedTid;
		void cacheTid();
		inline int tid() {
			if (cacheTid == 0) {
				cacheTid();
			}
			return t_cachedTid;
		}
	} // namespace CurrentThread

} // namespace echo

#endif