#include <Apps/BaseApp.h>
#include <Apps/DeferredRenderingApp.h>

using namespace std;
using namespace baselib;

#include <Logging/Log.h>

int main(int arc, char** argv)
{
	Logger::setAddTimeStamp(false);
	Logger::setLogLevel(LOGLEVEL_VERBOSE);

	//BaseApp app; 
	DeferredRenderingApp app;
	app.setSize(800, 600);
	app.setFullScreen(false);
	app.setGLVersion(3, 2);
	app.setWindowTitle("Basic Deferred Rendering Test");
	app.start();
	return 0;
}