#include <assert.h>
#include "xf/xf.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/timeout.h"
#include "xf/initialevent.h"
#include "xf/behavior.h"
#include "trace/trace.h"
using interface::XFResourceFactory;

XFBehavior::XFBehavior(bool ownDispatcher)
{
    this->_hasOwnDispatcher = ownDispatcher;
    if(this->_hasOwnDispatcher)
        this->_pDispatcher = XFResourceFactory::getInstance()->createDispatcher() ;
    else{
        this->_pDispatcher = XFResourceFactory::getInstance()->getDefaultDispatcher();
    }
    this->_pCurrentEvent = nullptr;
    this->deleteOnTerminate_ = true; 
}

XFBehavior::~XFBehavior()
{
    Trace::out("Behaviour destructor");
    if(this->_hasOwnDispatcher)
    {
        Trace::out("Behaviour destructor stop");
        this->getDispatcher()->stop();
    }
}

void XFBehavior::startBehavior()
{
    this->pushEvent(new XFInitialEvent());
}

void XFBehavior::pushEvent(XFEvent *pEvent)
{
    if(!pEvent->getBehavior())
        pEvent->setBehavior(this);
    if(pEvent)
        this->_pDispatcher->pushEvent(pEvent);
}

bool XFBehavior::deleteOnTerminate() const
{
    return deleteOnTerminate_;
}

void XFBehavior::setDeleteOnTerminate(bool deleteBehaviour)
{
    this->deleteOnTerminate_ = deleteBehaviour;
}

const XFEvent *XFBehavior::getCurrentEvent() const
{
    return this->_pCurrentEvent;
}

interface::XFDispatcher *XFBehavior::getDispatcher()
{
    return this->_pDispatcher;
}

const XFTimeout *XFBehavior::getCurrentTimeout()
{
    if(this->_pCurrentEvent->getEventType() == XFEvent::XFEventType::Timeout)
        return  (XFTimeout *)this->_pCurrentEvent;
    return nullptr;
}
void XFBehavior::setCurrentEvent(const XFEvent *pEvent)
{
    this->_pCurrentEvent = pEvent;
}

interface::XFReactive::TerminateBehavior XFBehavior::process(const XFEvent *pEvent)
{
    this->setCurrentEvent(pEvent);

    XFEventStatus status;
    status = this->processEvent();
    return (status==XFEventStatus::Terminate);
}
