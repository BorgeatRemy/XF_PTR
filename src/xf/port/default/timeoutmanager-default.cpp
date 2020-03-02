
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "xf/interface/mutex.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"
#include "trace/trace.h"
#include "xf/interface/reactive.h"
using interface::XFMutex;

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
    return XFTimeoutManagerDefault::getInstance();
}

// TODO: Implement code for XFTimeoutManagerDefault class
XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
    if(this->_pMutex)
        delete this->_pMutex;
    while(this->_timeouts.size()>0)
    {
        delete this->_timeouts.front();
        this->_timeouts.pop_front();
    }
}

interface::XFTimeoutManager *XFTimeoutManagerDefault::getInstance()
{
    static XFTimeoutManagerDefault instance;
    return &instance;
}

void XFTimeoutManagerDefault::start()
{
    XF_startTimeoutManagerTimer(this->getTickInterval());
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    this->addTimeout(new XFTimeout(timeoutId,interval,pReactive));
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{
    std::list<XFTimeout *>::iterator it;
    XFTimeout unscheduledTimeout =  XFTimeout(timeoutId,0,pReactive);
    int countToExecute = 0;

    //enter critical section
    this->_pMutex->lock();

    //search thorugh the entire list
    for(it = this->_timeouts.begin();it!=this->_timeouts.end();it++)
    {
        //true if the timeout must be unschedule
        if(*(*it)==unscheduledTimeout)
        {
            //get number of remaining ticks of the unschedule timeout
            countToExecute = (*it)->getRelTicks();
            //delete this timeout and remove it from de list
            delete (*it);
            it++;

            this->_timeouts.remove((*std::prev(it,1)));

            //if the element exists
            if(it!=this->_timeouts.end())
            {
                //update number of ticks
                (*it)->substractFromRelTicks(countToExecute);
            }
        }
    }
    //leave critical section
    this->_pMutex->unlock();
}

void XFTimeoutManagerDefault::tick()
{
     int nTickToSub = this->getTickInterval();
    XFTimeout* deleteTimeout;

    this->_pMutex->lock();

    while(!this->_timeouts.empty())
    {
        deleteTimeout = this->_timeouts.front();
        deleteTimeout->substractFromRelTicks(nTickToSub);

        //first elem has timemout?
        if(deleteTimeout->getRelTicks()<=0)
        {
            nTickToSub = -deleteTimeout->getRelTicks();

            //return the timeout
            this->returnTimeout(deleteTimeout);

            //remove timemout from the list
            this->_timeouts.pop_front();
        }
        else
        {
            break;
        }
    }

    this->_pMutex->unlock();
}

XFTimeoutManagerDefault::XFTimeoutManagerDefault()
{
    this->_pMutex = XFMutex::create();
}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{
    std::list<XFTimeout *>::iterator it;
    int count = 0;
    bool isEnd = true;

    //enter in critcal section
    this->_pMutex->lock();

    //go through the list to put the new timeout at his emplacement
    for(it= this->_timeouts.begin();it!=this->_timeouts.end();++it)
    {
        // compare to number of ticks of the new timeout
        if(pNewTimeout->getRelTicks()<count + (*it)->getRelTicks())
        {
            // insert in the list
            this->_timeouts.insert(it,pNewTimeout);
            // set the number o ticks to execute
            pNewTimeout->substractFromRelTicks(count);

            //change value of the next element
            (*it)->substractFromRelTicks(pNewTimeout->getRelTicks());
            isEnd = false;
            break;
        }
        // get total number of ticks
        count += (*it)->getRelTicks();
    }
    //the element is the last one of the list
    if(isEnd)
    {
        pNewTimeout->substractFromRelTicks(count);
        this->_timeouts.push_back(pNewTimeout);
    }
    //end of critical section
    this->_pMutex->unlock();
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    //push an new event in the event queue
    if(pTimeout->getBehavior())
        pTimeout->getBehavior()->pushEvent(pTimeout);
}

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION


