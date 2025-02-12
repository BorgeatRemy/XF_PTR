#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;

bool XF::_bInitialized = false;

void XF_exec()
{
	XF::exec();
}

void XF_execOnce()
{
	XF::execOnce();
}

void XF_initialize(int timeInterval)
{
	XF::initialize(timeInterval);
}

int XF::execOnce()
{
	return XFResourceFactory::getInstance()->getDefaultDispatcher()->executeOnce();
}

int XF::exec()
{
	XFResourceFactory::getInstance()->getDefaultDispatcher()->start();
	XFResourceFactory::getInstance()->getDefaultDispatcher()->execute();
	return 0;
}

void XF::initialize(int timeInterval, int argc, char* argv[])
{
	if(_bInitialized == false)
	{
        // Create and initialize TimeoutManager
        interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
        // Start it
        interface::XFTimeoutManager::getInstance()->start();
        _bInitialized = true;
	}
}

#endif // USE_XF_DEFAULT_IMPLEMENTATION
