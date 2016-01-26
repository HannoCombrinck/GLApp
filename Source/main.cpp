#include <Tetris/Tetris.h>

using namespace std;
using namespace tetris;

int main(int arc, char** argv)
{
	Tetris t;
	t.setSize(512, 512);
	t.setFullScreen(false);
	t.setWindowTitle("Tetris");
	t.start();

	return 0;
}