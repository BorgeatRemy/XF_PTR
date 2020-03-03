#include <config/xf-config.h>

#if (USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION != 0)

#include <assert.h>
#include <string.h>
#include "thread-default.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

using namespace interface;

void XFThreadDefault::start()
{
    this->QThread::start();
}

void XFThreadDefault::stop()
{
    this->QThread::quit();
    this->QThread::wait(500);
    //this->QThread::wait(); // ensure thread is closed before quitting
    this->QThread::deleteLater();
}

void XFThreadDefault::setPriority(XFThreadPriority priority)
{
    // Set prio following a circa relation between priorities
    this->QThread::setPriority(xfPrioToQThreadPrio(priority));
}

XFThreadPriority XFThreadDefault::getPriority() const
{
    // Set prio following a circa relation between priorities
    return qthreadPrioToXFPrio(this->QThread::priority());
}

void XFThreadDefault::delay(uint32_t milliseconds)
{
    this->QThread::sleep(milliseconds);
}

XFThreadDefault::XFThreadDefault(interface::XFThreadEntryPointProvider *pProvider,
                                 interface::XFThread::EntryMethodBody entryMethod,
                                 const char *threadName, const uint32_t stackSize)
{
    this->_pEntryMethodProvider = pProvider;
    this->_entryMethod = entryMethod;
    this->QThread::setObjectName(threadName);
    this->QThread::setStackSize(stackSize);
}

void XFThreadDefault::run()
{
    (this->_pEntryMethodProvider->*this->_entryMethod)(this);
}

QThread::Priority XFThreadDefault::xfPrioToQThreadPrio(XFThreadPriority prio)
{
    // Relation between priorities
    switch(prio)
    {
        case XF_THREAD_PRIO_UNKNOWN:
            return QThread::Priority::InheritPriority;
        case XF_THREAD_PRIO_LOW:
            return QThread::Priority::LowPriority;
        case XF_THREAD_PRIO_NORMAL:
            return QThread::Priority::NormalPriority;
        case XF_THREAD_PRIO_HIGH:
            return QThread::Priority::HighPriority;
        case XF_THREAD_PRIO_MAX:
            return QThread::Priority::TimeCriticalPriority;
    }
    return QThread::Priority::InheritPriority;
}

XFThreadPriority XFThreadDefault::qthreadPrioToXFPrio(const QThread::Priority prio)
{
    // Relation between priorities
    switch(prio)
    {
        case QThread::IdlePriority:
        case QThread::LowestPriority:
        case QThread::LowPriority:
            return XF_THREAD_PRIO_LOW;
        case QThread::NormalPriority:
            return XF_THREAD_PRIO_NORMAL;
        case QThread::HighPriority:
            return XF_THREAD_PRIO_HIGH;
        case QThread::HighestPriority:
        case QThread::TimeCriticalPriority:
            return XF_THREAD_PRIO_MAX;
        case QThread::InheritPriority:
            return XF_THREAD_PRIO_UNKNOWN;
    }
    return XF_THREAD_PRIO_UNKNOWN;
}

#endif // USE_XF_THREAD_DEFAULT_QT_IMPLEMENTATION
