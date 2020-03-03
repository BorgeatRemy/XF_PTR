#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "resourcefactory-default.h"
#include "mutex-default.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
	return XFResourceFactoryDefault::getInstance();
}

interface::XFResourceFactory* XFResourceFactoryDefault::getInstance()
{
    static XFResourceFactoryDefault inst;
    return &inst;
}

interface::XFDispatcher* XFResourceFactoryDefault::getDefaultDispatcher()
{
   static XFDispatcherDefault default_instance;
   return &default_instance;
}

interface::XFDispatcher* XFResourceFactoryDefault::createDispatcher()
{
	return new XFDispatcherDefault();
}

interface::XFThread* XFResourceFactoryDefault::createThread(
		interface::XFThreadEntryPointProvider* pProvider,
		interface::XFThread::EntryMethodBody entryMethod,
		const char* threadName, const uint32_t stackSize)
{

}

interface::XFMutex* XFResourceFactoryDefault::createMutex()
{
	return new XFMutexDefault();
}


#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION
