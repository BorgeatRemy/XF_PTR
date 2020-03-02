#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;


void XF::initialize(int timeInterval /* = 10 */, int argc /* = 0 */, char * argv[] /* = nullptr */)
{
    if (!_bInitialized)
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

    // Loop
    bool nexit = true;
    while(nexit)
    {
    	nexit = XF::execOnce() == 0?false:true;
    }
    return 0;
}

int XF::execOnce()
{
	// TODO
    return 0;
}

void XF::terminateApp()
{
    assert(0); // not by default
}

#endif // USE_XF_DEFAULT_IMPLEMENTATION
