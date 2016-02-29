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

		struct VertexPos
		{
			VertexPos(const Vec3& _vPos)
				: vPos(_vPos) {}

			Vec3 vPos;
		};
	}

	std::shared_ptr<StaticGeometry> createQuad()
	{
		auto spVL = VertexLayout::create();
		spVL->add("position", 3, TYPE_FLOAT);
		spVL->add("texcoord", 2, TYPE_FLOAT, true);

		auto spVertexList = std::shared_ptr<VertexList<VertexPosUV>>(new VertexList<VertexPosUV>(spVL));
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

	std::shared_ptr<StaticGeometry> createGrid(int iLines, float fLineSpacing, bool xzPlane/*=true*/, bool xyPlane/*=false*/, bool yzPlane/*=false*/)
	{
		auto spVL = VertexLayout::create();
		spVL->add("position", 3, TYPE_FLOAT);

		float fHalfLength = float(iLines - 1) * fLineSpacing;

		auto spVertexList = std::shared_ptr<VertexList<VertexPos>>(new VertexList<VertexPos>(spVL));
		for (int i = -iLines; i <= iLines; ++i)
		{
			float fOffset = float(i) * fLineSpacing;

			if (xzPlane)
			{
				spVertexList->addVertex(VertexPos(Vec3(fOffset, 0.0f, -fHalfLength)));
				spVertexList->addVertex(VertexPos(Vec3(fOffset, 0.0f, fHalfLength)));

				spVertexList->addVertex(VertexPos(Vec3(-fHalfLength, 0.0f, fOffset)));
				spVertexList->addVertex(VertexPos(Vec3(fHalfLength, 0.0f, fOffset)));
			}

			if (xyPlane)
			{
				spVertexList->addVertex(VertexPos(Vec3(fOffset, -fHalfLength, 0.0f)));
				spVertexList->addVertex(VertexPos(Vec3(fOffset, fHalfLength, 0.0f)));

				spVertexList->addVertex(VertexPos(Vec3(-fHalfLength, fOffset, 0.0f)));
				spVertexList->addVertex(VertexPos(Vec3(fHalfLength, fOffset, 0.0f)));
			}

			if (yzPlane)
			{
				spVertexList->addVertex(VertexPos(Vec3(0.0f, fOffset, -fHalfLength)));
				spVertexList->addVertex(VertexPos(Vec3(0.0f, fOffset, fHalfLength)));

				spVertexList->addVertex(VertexPos(Vec3(0.0f, -fHalfLength, fOffset)));
				spVertexList->addVertex(VertexPos(Vec3(0.0f, fHalfLength, fOffset)));
			}
		}

		return StaticGeometry::create(spVertexList, Geometry::LINES);
	}

} }