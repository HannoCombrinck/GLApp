#include <Tetris/Tetris.h>

using namespace std;
using namespace tetris;

int main(int arc, char** argv)
{
	Tetris t;
	t.setSize(1024, 768);
	t.setFullScreen(false);
	t.setGLVersion(3, 2);
	t.setWindowTitle("Tetris");
	t.start();

	return 0;
}