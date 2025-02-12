#ifndef INITIALEVENT_H
#define INITIALEVENT_H

#include "xf/event.h"
#include "xf.h"

/** @ingroup xf_core
 *  @{
 */

/**
 * @brief Initial event to start a behavior.
 *
 * Represents for example the first transition executed
 * in a state machine.
 */
class XFInitialEvent : public XFEvent
{
public:
    XFInitialEvent();
    //XFInitialEvent(interface::XFReactive * pBehavior);

    bool deleteAfterConsume() const override;
};

/** @} */ // end of xf_core group
#endif // INITIALEVENT_H
