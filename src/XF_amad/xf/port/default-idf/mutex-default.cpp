#include <config/xf-config.h>

#if (USE_XF_MUTEX_DEFAULT_IDF_IMPLEMENTATION != 0)

#include "critical/critical.h"	// Provided by the platform used
#include "mutex-default.h"
#include "assert.h"

interface::XFMutex * interface::XFMutex::create()
{
	// TODO : can really have a NEW mutex ?
    return new XFMutexDefault;
}

void XFMutexDefault::lock()
{
    enterCritical();
}

void XFMutexDefault::unlock()
{
    exitCritical();
}

bool XFMutexDefault::tryLock(int32_t timeout)
{
    // impossible for this application
	assert(0);
	return false;
}

#endif // USE_XF_MUTEX_DEFAULT_IDF_IMPLEMENTATION
