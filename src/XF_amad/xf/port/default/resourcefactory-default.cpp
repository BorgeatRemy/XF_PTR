#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "resourcefactory-default.h"
#include "mutex-default.h"
#include "assert.h"

static XFResourceFactoryDefault inst;

//static
interface::XFResourceFactory * getInstance()
{
	return &inst;
}

interface::XFDispatcher *interface::XFResourceFactory::getDefaultDispatcher()
{
	static XFDispatcherDefault def_disp;
	return &def_disp;
}

interface::XFDispatcher *interface::XFResourceFactory::createDispatcher()
{
	return new XFDispatcherDefault();
}

interface::XFThread *interface::XFResourceFactory::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
	// impossible here
	assert(0);
	return nullptr;
}

interface::XFMutex *interface::XFResourceFactory::createMutex()
{
	return XFMutex::create();
}

#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION
