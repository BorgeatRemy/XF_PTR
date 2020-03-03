#include "xf/timeout.h"


XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior) : XFEvent(XFEvent::XFEventType::Timeout,id,pBehavior)
{
    this->_interval = interval;
    this->_relTicks = interval;
}

bool XFTimeout::operator ==(const XFTimeout &timeout) const
{
    return (this->getId() == timeout.getId()) && (this->getBehavior() == timeout.getBehavior());
}

bool XFTimeout::deleteAfterConsume() const
{
    return true;
}
