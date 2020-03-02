#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION != 0)
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-default.h"
#include "xf/port/default/resourcefactory-default.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;
using interface::XFReactive;
using interface::XFMutex;

XFDispatcherDefault::XFDispatcherDefault()
{
	this->_bExecuting = false;
	this->_pMutex = XFResourceFactoryDefault::getInstance()->createMutex();
}

XFDispatcherDefault::~XFDispatcherDefault()
{
	if(this->_pMutex)
		delete this->_pMutex;
}

void XFDispatcherDefault::start()
{
    _bExecuting = true;
}

void XFDispatcherDefault::stop()
{
    _bExecuting = false;
}

void XFDispatcherDefault::pushEvent(XFEvent * pEvent)
{
#if defined(XF_TRACE_EVENT_PUSH_POP) && (XF_TRACE_EVENT_PUSH_POP != 0)
        Trace::out("Push event: 0x%x", pEvent);
#endif // XF_TRACE_EVENT_PUSH_POP
        _events.push(pEvent);
}

void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

void XFDispatcherDefault::unscheduleTimeout(int timeoutId, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

int XFDispatcherDefault::execute(const void * param /* = nullptr */)
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

int XFDispatcherDefault::executeOnce()
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

void XFDispatcherDefault::dispatchEvent(const XFEvent * pEvent) const
{
    if(pEvent->getBehavior())
        if(pEvent->getBehavior()->process(pEvent)) // is a terminate event
            if(pEvent->getBehavior()->deleteOnTerminate()) // needs to be deleted
                delete pEvent->getBehavior();
}

#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION
