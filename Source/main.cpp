#include <BaseApp.h>

using namespace std;
using namespace baselib;

int main(int arc, char** argv)
{
	BaseApp app; // Default constructor uses default window settings (window size etc.)
	app.start();
	
	system("pause");
	return 0;
}