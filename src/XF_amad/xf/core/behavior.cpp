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
    // Create or get default dispatcher
    if(this->_hasOwnDispatcher)
        this->_pDispatcher = XFResourceFactory::getInstance()->createDispatcher();
    else
        this->_pDispatcher = XFResourceFactory::getInstance()->getDefaultDispatcher();
    this->deleteOnTerminate_ = true;
    this->_pCurrentEvent = nullptr;
}

XFBehavior::~XFBehavior()
{
    // Destroy only if own dispatcher created
    //if(_hasOwnDispatcher)
        //delete this->_pDispatcher;
    if(_hasOwnDispatcher)
        this->_pDispatcher->stop();
}

void XFBehavior::startBehavior()
{
    // start dispatcher (no problem with multiple start call)
    this->_pDispatcher->start();
    // push an initial event
    this->pushEvent(new XFInitialEvent());
}

void XFBehavior::pushEvent(XFEvent *pEvent)
{
    // set this behavior for callback if none is set
    if(!pEvent->getBehavior())
        pEvent->setBehavior(this);
    // push an event
    this->_pDispatcher->pushEvent(pEvent);
}

bool XFBehavior::deleteOnTerminate() const
{
    //return this->deleteOnTerminate_;
    /*if(this->deleteOnTerminate_)
    {
        delete this;
        return true;
    }*/
    return this->deleteOnTerminate_;
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
    if(this->_pCurrentEvent->getEventType() == XFEvent::Timeout)
    {
        return (XFTimeout*)this->_pCurrentEvent;
    }
    return nullptr;
}

void XFBehavior::setCurrentEvent(const XFEvent *pEvent)
{
    this->_pCurrentEvent = pEvent;
}

interface::XFReactive::TerminateBehavior XFBehavior::process(const XFEvent *pEvent)
{
    // register and process event
    this->setCurrentEvent(pEvent);
    XFEventStatus stat = this->processEvent();
    // if needs to termintae this
    if(stat == XFEventStatus::Terminate)
    {
        this->deleteOnTerminate();
        return true;
    }
    return stat==XFEventStatus::Terminate;

}
