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

using interface::XFTimeoutManager;
using interface::XFResourceFactory;
using interface::XFReactive;
using interface::XFMutex;

XFDispatcherDefault::XFDispatcherDefault()
{
	this->_bExecuting = false;
	this->_pMutex = XFMutex::create();
}

XFDispatcherDefault::~XFDispatcherDefault()
{
	if(this->_pMutex)
		delete this->_pMutex;

	//delete events list
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

void XFDispatcherDefault::start()
{
	this->_bExecuting = true;
}

void XFDispatcherDefault::stop()
{
	this->_bExecuting = false;

}

void XFDispatcherDefault::pushEvent(XFEvent* pEvent)
{
	this->_events.push(pEvent);
}

void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval,
		interface::XFReactive* pReactive)
{
	XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId,interval,pReactive);

}

void XFDispatcherDefault::unscheduleTimeout(int timeoutId,
		interface::XFReactive* pReactive)
{

	XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId,pReactive);

}

int XFDispatcherDefault::execute(const void* param)
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
}

int XFDispatcherDefault::executeOnce()
{
    const XFEvent* eventExectuted;
    // TODO: Implement code for XFDispatcherActiveDefault::executeOnce
    if(!this->_events.empty())
    {
        eventExectuted = this->_events.front();
        this->dispatchEvent(eventExectuted);

        this->_events.pop();
        if(eventExectuted->deleteAfterConsume())
        {
            delete eventExectuted;
        }
        else
        {
            this->_events.push(eventExectuted);
        }
    }
    return _bExecuting;
}

void XFDispatcherDefault::dispatchEvent(const XFEvent* pEvent) const
{
    if(pEvent->getBehavior())
     {
        //dispatch the event, if it's an terminateEvent and the state machine must be deletet
        if(pEvent->getBehavior()->process(pEvent) && pEvent->getBehavior()->deleteOnTerminate())
        {
            //delete state machine
            delete pEvent->getBehavior();
        }
    }
}

// TODO: Implement code for XFDispatcherDefault class

#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION
