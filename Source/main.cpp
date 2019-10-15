#include <TestApps/DeferredRenderingApp.h>

using namespace std;
using namespace baselib;

int main(int arc, char** argv)
{
	DeferredRenderingApp app;
	app.setPosition(100, 100);
	app.setSize(512, 512);
	app.setFullScreen(false);
	app.setWindowTitle("Deferred rendering test");
	app.start();

	return 0;
}