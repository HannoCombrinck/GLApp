#include <ModelViewer/ModelViewer.h>

using namespace std;

int main(int arc, char** argv)
{
	ModelViewer t;
	t.setSize(512, 512);
	t.setFullScreen(false);
	t.setWindowTitle("ModelViewer");
	t.start();

	return 0;
}