
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "xf/interface/mutex.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"
#include "xf/interface/resourcefactory.h"

using interface::XFMutex;

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
    // Create static default instance
    static XFTimeoutManagerDefault inst;
    return &inst;
}

XFTimeoutManagerDefault::XFTimeoutManagerDefault()
{
    // Create the mutex used to protect timeout list access
    this->_pMutex = interface::XFResourceFactory::getInstance()->createMutex();
}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
    // Delete protection mutex
    delete this->_pMutex;
    while(this->_timeouts.size()>0)
    {
        delete this->_timeouts.front();
        this->_timeouts.pop_front();
    }
}

void XFTimeoutManagerDefault::start()
{
    assert(this->getTickInterval()!=0); // Ensure tick has been set
    // Start TimeoutManager with set tick
    XF_startTimeoutManagerTimer(this->getTickInterval());
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    this->addTimeout(new XFTimeout(timeoutId,interval,pReactive));
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{
    XFTimeout tim = XFTimeout(timeoutId,0,pReactive);
    int32_t count = 0;  // delta ticks count
    int32_t delta = 0; // delta between insertion place and old timeout

    this->_pMutex->lock();

    for(TimeoutList::iterator iter = this->_timeouts.begin(); iter != this->_timeouts.end(); iter++)
    {
        // Add ticks first
        count += (*iter)->getRelTicks();

        // search for the element to remove
        if(*(*iter) == tim)
        {
            // found it, remove and rearrange timings
            iter++;
            TimeoutList::iterator rearrTime = iter; // element we need to modify timings
            iter--; // recover current element
            // remove element from list and delete it
            this->_timeouts.erase(iter);
            // rearrange timings if has a next timer
            if(rearrTime != this->_timeouts.end())
                (*rearrTime)->addToRelTicks((count-delta));
            break;
        }

        // Same as count, but with one element late for if() above
        delta += (*iter)->getRelTicks();
    }

    this->_pMutex->unlock();
}

void XFTimeoutManagerDefault::tick()
{
    // List to get events and unlock mutex before push
    TimeoutList temp;

    this->_pMutex->lock();

    if(this->_timeouts.size() > 0) // ensure we have at least a timeout
    {
        // Substract only from first
        this->_timeouts.front()->substractFromRelTicks(this->getTickInterval());
        // If < 0, push event that will be destroyed by eventmanager
        while(this->_timeouts.front()->getRelTicks() <= 0)
        {
            // remove from list and register, don't delete as it will be by event manager
            temp.push_back(this->_timeouts.front());
            this->_timeouts.pop_front();
            // ensure we don't pop with no events
            if(this->_timeouts.size() == 0)
                break;
        }
    }

    this->_pMutex->unlock();

    // Push all events
    for(auto t : temp)
        this->returnTimeout(t);
}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{
    int32_t count = 0;  // delta ticks count
    int32_t delta = 0; // delta between insertion place and old timeout
    bool placed = false; // ensure event was pushed in queue, else is last place

    this->_pMutex->lock();

    for(TimeoutList::iterator iter = this->_timeouts.begin(); iter != this->_timeouts.end(); iter++)
    {
        // Add ticks first, so could be set on first place
        count += (*iter)->getRelTicks();
        // look for next timeout place
        if(pNewTimeout->getRelTicks() < (*iter)->getRelTicks()+count)
        {
            // we have the place where to add timeout
            pNewTimeout->substractFromRelTicks(delta); // set new rel tick
            this->_timeouts.insert(iter,pNewTimeout); // as iter is on the element bigger than, insert will insert before
            placed = true;
            // set new time for moved element
            (*iter)->setRelTicks((count-delta)-pNewTimeout->getRelTicks());
            break;
        }
        // Same as count, but with one element late for if() above
        delta += (*iter)->getRelTicks();
    }
    // If not placed, is last element in the list
    if(!placed)
    {
        pNewTimeout->substractFromRelTicks(count);
        this->_timeouts.push_back(pNewTimeout);
    }

    this->_pMutex->unlock();
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    if(pTimeout->getBehavior())
        pTimeout->getBehavior()->pushEvent(pTimeout);
}

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
