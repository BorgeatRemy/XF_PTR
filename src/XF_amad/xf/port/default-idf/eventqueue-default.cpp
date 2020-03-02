#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IDF_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue-default.h"
#include "xf/port/default/resourcefactory-default.h"

XFEventQueueDefault::XFEventQueueDefault()
{
	this->_mutex = *XFResourceFactoryDefault::getInstance()->createMutex();
}

XFEventQueueDefault::~XFEventQueueDefault()
{
	if(&this->_mutex)
		delete &this->_mutex;
}

bool XFEventQueueDefault::empty() const
{
    return this->_queue.empty();
}

bool XFEventQueueDefault::push(const XFEvent * pEvent)
{
	this->_mutex.lock();
	this->_queue.push(pEvent);
	this->_mutex.unlock();
    return true;
}

const XFEvent * XFEventQueueDefault::front()
{
    return this->_queue.front();
}

void XFEventQueueDefault::pop()
{
	this->_mutex.lock();
	this->_queue.pop();
	this->_mutex.unlock();
}

bool XFEventQueueDefault::pend()
{
	while(this->_queue.size() != 0){}
	return true;
}

#endif // USE_XF_EVENT_QUEUE_DEFAULT_IDF_IMPLEMENTATION
