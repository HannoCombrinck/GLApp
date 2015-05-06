#include "GeometryHelpers.h"

#include <Graphics/VertexList.h>

namespace baselib { namespace graphics {
	
	namespace
	{
		struct VertexPosUV
		{
			VertexPosUV(const Vec3& _vPos, const Vec2& _vUV)
				: vPos(_vPos)
				, vUV(_vUV) {}

			Vec3 vPos;
			Vec2 vUV;
		};
	}

	boost::shared_ptr<StaticGeometry> createQuadGeometry()
	{
		auto spVL = VertexLayout::create();
		spVL->add("position", 3, TYPE_FLOAT);
		spVL->add("texcoord", 2, TYPE_FLOAT, true);

		auto spVertexList = boost::shared_ptr<VertexList<VertexPosUV>>(new VertexList<VertexPosUV>(spVL));
		spVertexList->addVertex(VertexPosUV(Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0, 0.0)));
		spVertexList->addVertex(VertexPosUV(Vec3(1.0f, -1.0f, 0.0f), Vec2(1.0, 0.0)));
		spVertexList->addVertex(VertexPosUV(Vec3(1.0f, 1.0f, 0.0f), Vec2(1.0, 1.0)));
		spVertexList->addVertex(VertexPosUV(Vec3(-1.0f, 1.0f, 0.0f), Vec2(0.0, 1.0)));
		spVertexList->addIndex(0);
		spVertexList->addIndex(1);
		spVertexList->addIndex(2);
		spVertexList->addIndex(0);
		spVertexList->addIndex(2);
		spVertexList->addIndex(3);

		return StaticGeometry::create(spVertexList, Geometry::TRIANGLES);
	}

} }