#include "xf/initialevent.h"

XFInitialEvent::XFInitialEvent() : XFEvent(XFEvent::XFEventType::Initial,0,nullptr)
{}

/*XFInitialEvent::XFInitialEvent(interface::XFReactive *pBehavior) : XFEvent(XFEvent::XFEventType::Initial,0,pBehavior)
{}*/

bool XFInitialEvent::deleteAfterConsume() const
{
    return true;
}
