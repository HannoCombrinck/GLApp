#include <BaseApp.h>

using namespace std;
using namespace baselib;
using namespace baselib::graphics;

#include <Logging/Log.h>
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
	auto spVL = boost::shared_ptr<VertexLayout>(new VertexLayout());
	spVL->add(VertexAttribute("position", 0, 3, TYPE_FLOAT, 0));
	spVL->add(VertexAttribute("normal", 1, 3, TYPE_FLOAT, 3*sizeof(float)));
	spVL->add(VertexAttribute("texcoord", 2, 2, TYPE_FLOAT, 6*sizeof(float)));

	auto spVertexList = boost::shared_ptr<VertexList<MyVert>>(new VertexList<MyVert>(spVL));
	spVertexList->addVertex(MyVert(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0, 0.0)));
	spVertexList->addVertex(MyVert(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 0.0)));
	spVertexList->addVertex(MyVert(Vec3(1.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 1.0)));
	spVertexList->addIndex(0);
	spVertexList->addIndex(1);
	spVertexList->addIndex(2);


	boost::shared_ptr<VertexListInterface> spVerts = spVertexList;
	auto spL = spVerts->getVertexLayout();
	for (unsigned int i = 0; i < spL->getAttributes().size(); ++i)
	{
		LOG_INFO << spL->getAttributes()[i].sName << ", " << spL->getAttributes()[i].iNumElements << ", " << spL->getAttributes()[i].iOffset;
	}
}

int main(int arc, char** argv)
{
	Logger::SetAddTimeStamp(false);

	testFunc();
	system("pause");

	BaseApp app(640, 480, false, 3, 2, "GLFWApp"); 
	app.start();
	return 0;
}