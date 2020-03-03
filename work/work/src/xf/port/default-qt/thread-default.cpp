#include <config/xf-config.h>
#include "trace/trace.h"
#if (USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION != 0)

#include <assert.h>
#include <string.h>
#include "thread-default.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

void XFThreadDefault::start()
{
    this->QThread::start();
}

void XFThreadDefault::stop()
{
    Trace::out("stop thread");
    this->QThread::terminate();
    this->QThread::wait();
    this->QThread::deleteLater();
}

void XFThreadDefault::setPriority(XFThreadPriority priority)
{
    switch(priority)
    {
        case XFThreadPriority::XF_THREAD_PRIO_UNKNOWN:
            this->QThread::setPriority(QThread::Priority::InheritPriority);
        break;
        case XFThreadPriority::XF_THREAD_PRIO_LOW:
            this->QThread::setPriority(QThread::Priority::LowPriority);
        break;
        case XFThreadPriority::XF_THREAD_PRIO_NORMAL:
            this->QThread::setPriority(QThread::Priority::NormalPriority);
        break;
        case XFThreadPriority::XF_THREAD_PRIO_HIGH:
            this->QThread::setPriority(QThread::Priority::HighPriority);
        break;
        case XFThreadPriority::XF_THREAD_PRIO_MAX:
            this->QThread::setPriority(QThread::Priority::TimeCriticalPriority);
        break;
    }
}

XFThreadPriority XFThreadDefault::getPriority() const
{
    switch(this->priority())
    {
        case QThread::Priority::InheritPriority:
            return XFThreadPriority::XF_THREAD_PRIO_UNKNOWN;
        case QThread::Priority::IdlePriority:
        case QThread::Priority::LowestPriority:
        case QThread::Priority::LowPriority:
            return XFThreadPriority::XF_THREAD_PRIO_LOW;
        case QThread::Priority::NormalPriority:
            return XFThreadPriority::XF_THREAD_PRIO_NORMAL;
        case QThread::Priority::HighPriority:
        case QThread::Priority::HighestPriority:
            return XFThreadPriority::XF_THREAD_PRIO_HIGH;
        case QThread::Priority::TimeCriticalPriority:
            return XFThreadPriority::XF_THREAD_PRIO_MAX;
        default:
            return XFThreadPriority::XF_THREAD_PRIO_UNKNOWN;
    }
}

void XFThreadDefault::delay(uint32_t milliseconds)
{
    this->sleep(milliseconds);
}

XFThreadDefault::XFThreadDefault(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    this->_pEntryMethodProvider = pProvider;
    this->_entryMethod = entryMethod;
    this->setObjectName(threadName);
    if(stackSize==0)
        this->setStackSize(XFTHREAD_DEFAULT_STACK_SIZE);
    else
        this->setStackSize(stackSize);

}

void XFThreadDefault::run()
{
   (_pEntryMethodProvider->*_entryMethod)(nullptr);
}


#endif // USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION

