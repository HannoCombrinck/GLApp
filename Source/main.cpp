#include <Apps/BaseApp.h>
#include <Apps/DeferredRenderingApp.h>

using namespace std;
using namespace baselib;

#include <Logging/Log.h>

int main(int arc, char** argv)
{
	Logger::setAddTimeStamp(false);
	Logger::setLogLevel(LOGLEVEL_INFO);

	//BaseApp app; 
	DeferredRenderingApp app;
	//app.setSize(1920, 1080);
	app.setSize(1280, 960);
	app.setFullScreen(false);
	app.setGLVersion(3, 2);
	app.setWindowTitle("Basic Deferred Rendering Test");
	app.start();
	return 0;
}