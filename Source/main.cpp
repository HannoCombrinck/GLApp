#include <BaseApp.h>

using namespace std;
using namespace baselib;
using namespace baselib::graphics;

#include <Graphics/VertexList.h>
#include <Math/Math.h>

struct MyVert
{
	MyVert(Vec3 vP, Vec3 vN, Vec2 _vUV)
		: vPos(vP)
		, vNormal(vN)
		, vUV(_vUV) {}

	Vec3 vPos;
	Vec3 vNormal;
	Vec2 vUV;
};

void testFunc() 
{
	VertexList<MyVert> vertexList;
	auto spVL = boost::shared_ptr<VertexLayout>(new VertexLayout());
	spVL->add(VertexAttribute("position", 0, 3, TYPE_FLOAT));
	spVL->add(VertexAttribute("normal", 1, 3, TYPE_FLOAT));
	spVL->add(VertexAttribute("texcoord", 2, 2, TYPE_FLOAT));
	vertexList.setVertexLayout(spVL);

	// Add triangle vertices
	vertexList.addVertex(MyVert(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0, 0.0)));
	vertexList.addVertex(MyVert(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 0.0)));
	vertexList.addVertex(MyVert(Vec3(1.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 1.0)));
}

int main(int arc, char** argv)
{
	testFunc();
	system("pause");

	BaseApp app; // Default constructor uses default window settings (window size etc.)
	app.start();
	return 0;
}