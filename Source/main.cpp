#include <iostream>

#include <GLFWApp/GLFWApp.h>

using namespace std;
using namespace baselib;

int main(int arc, char** argv)
{
	GLFWApp app;
	app.start();
	while (app.isAppRunning())
	{
		app.processEvents();
		app.swapBuffers();
	}
	app.destroy();
	
	system("pause");
	return 0;
}