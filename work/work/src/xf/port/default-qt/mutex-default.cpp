#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_MUTEX_DEFAULT_QT_IMPLEMENTATION != 0)

#include "mutex-default.h"


void XFMutexDefault::lock()
{
    this->_mutex.lock();
}

void XFMutexDefault::unlock()
{
    this->_mutex.unlock();
}

bool XFMutexDefault::tryLock(int32_t timeout)
{
    return this->_mutex.tryLock(timeout);
}

interface::XFMutex *interface::XFMutex::create()
{
     return new XFMutexDefault();
}

#endif // USE_XF_MUTEX_DEFAULT_QT_IMPLEMENTATION

