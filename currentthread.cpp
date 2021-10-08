#include "currentthread.h"

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

namespace echo
{
	namespace CurrentThread
	{
		// internal
		__thread int t_cachedTid = 0;

        void cacheTid() {
            if (t_cachedTid == 0) {
                t_cachedTid = ::syscall(SYS_gettid);
            }
        }
	} // namespace CurrentThread

} // namespace echo