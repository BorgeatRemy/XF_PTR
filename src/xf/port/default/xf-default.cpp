#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;

static bool XF::_bInitialized = false;

void XF::initialize(int timeInterval, int argc, char * argv[])
{
	if(!_bInitialized)
	{
        // Create and initialize TimeoutManager
        interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
        // Start it
        interface::XFTimeoutManager::getInstance()->start();

        _bInitialized = true;
	}
}

int XF::exec()
{
	 // Start default dispatcher
	XFResourceFactory::getInstance()->getDefaultDispatcher()->start();
}

int XF::execOnce()
{
	XFResourceFactory::getInstance()->getDefaultDispatcher()->execute();
}

void XF_initialize(int timeInterval)
{
	XF::initialize(timeInterval);
}

void XF_exec()
{
	XF::exec();
}

void XF_execOnce()
{
	XF::execOnce();
}

#endif // USE_XF_DEFAULT_IMPLEMENTATION
