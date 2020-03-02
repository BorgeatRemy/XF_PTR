#include "xf/nulltransition.h"


XFNullTransition::XFNullTransition(interface::XFReactive *pBehavior) : XFEvent(XFEvent::XFEventType::NullTransition,0,pBehavior)
{}

bool XFNullTransition::deleteAfterConsume() const
{
    return true;
}
