#include <BaseApp.h>

using namespace std;
using namespace baselib;

int main(int arc, char** argv)
{
	BaseApp app;
	// Set startup configuration before calling init - width, height, GL context version etc.
	// Otherwise hard coded defaults are used. 
	app.init();
	app.start();
	app.destroy();
	
	system("pause");
	return 0;
}