#include "xf/customevent.h"

XFCustomEvent::XFCustomEvent(int id, interface::XFReactive *pBehavior) : XFEvent(XFEvent::XFEventType::Event,id,pBehavior)
{
    this->_bDeleteAfterConsume = true;
}
