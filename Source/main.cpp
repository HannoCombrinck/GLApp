#include <Apps/BaseApp.h>

using namespace std;
using namespace baselib;

#include <Logging/Log.h>

int main(int arc, char** argv)
{
	Logger::setAddTimeStamp(false);
	Logger::setLogLevel(LOGLEVEL_VERBOSE);

	BaseApp app(640, 480, false, 3, 2, "GLFWApp"); 
	app.start();
	return 0;
}