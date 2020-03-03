#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#if defined(XF_TRACE_EVENT_PUSH_POP) && (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/thread.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-active.h"
#include "trace/trace.h"


//#define XF_TRACE_EVENT_PUSH_POP 3 // uncomment to enable push events commentary



using interface::XFTimeoutManager;
using interface::XFResourceFactory;
using interface::XFReactive;

XFDispatcherActiveDefault::XFDispatcherActiveDefault() :
    _bExecuting(false),
    _pThread(nullptr)
{
    // Create Thread
    _pThread = XFResourceFactory::getInstance()->createThread(this,
                                                              interface::XFThread::EntryMethodBody(&XFDispatcherActiveDefault::execute),
                                                              "dispatcherThread");
    assert(_pThread);
}

XFDispatcherActiveDefault::~XFDispatcherActiveDefault()
{
    _bExecuting = false;

    if (_pThread)
    {
        _pThread->stop();
        delete _pThread;
    }

    // Empty queue while destroying events
    while(!this->_events.empty())
    {
        if(this->_events.front()->deleteAfterConsume())
        {
            if(this->_events.front()->getBehavior())
                delete this->_events.front()->getBehavior();
            delete this->_events.front();
        }
        this->_events.pop();
    }
}

void XFDispatcherActiveDefault::start()
{
    assert(_pThread);
    _bExecuting = true;
    _pThread->start();
}

void XFDispatcherActiveDefault::stop()
{
    _bExecuting = false;
    _pThread->stop();
}

void XFDispatcherActiveDefault::pushEvent(XFEvent * pEvent)
{
#if defined(XF_TRACE_EVENT_PUSH_POP) && (XF_TRACE_EVENT_PUSH_POP != 0)
        Trace::out("Push event: 0x%x", pEvent);
#endif // XF_TRACE_EVENT_PUSH_POP
        _events.push(pEvent);
}

void XFDispatcherActiveDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

void XFDispatcherActiveDefault::unscheduleTimeout(int timeoutId, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

int XFDispatcherActiveDefault::execute(const void * param /* = nullptr */)
{
    (void)param;

    while(_bExecuting)
    {
        while (_events.empty() && _bExecuting)
        {
            _events.pend();	// Wait until something to do
        }

        executeOnce();
    }

    return 0;
}

int XFDispatcherActiveDefault::executeOnce()
{
    // dispatch event if any
    if(!this->_events.empty())
    {
        const XFEvent* evn = this->_events.front();
        this->dispatchEvent(evn);
        if(this->_events.front()->deleteAfterConsume()) // if shouldn't be consumed, repush it before poping
            delete this->_events.front();
        this->_events.pop();
    }
    return _bExecuting;
}

void XFDispatcherActiveDefault::dispatchEvent(const XFEvent * pEvent) const
{
    if(pEvent->getBehavior())
        if(pEvent->getBehavior()->process(pEvent)) // is a terminate event
            if(pEvent->getBehavior()->deleteOnTerminate()) // needs to be deleted
                delete pEvent->getBehavior();
}

#endif // USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION
