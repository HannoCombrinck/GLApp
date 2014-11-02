#include "ModelLoader.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/Node.h>
#include <Graphics/Visual.h>
#include <Graphics/VertexList.h>
#include <Graphics/StaticGeometry.h>
#include <Graphics/Material.h>
#include <Graphics/ShaderObject.h>
#include <Graphics/ShaderPipeline.h>
#include <Graphics/Shader.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib { namespace graphics {

	boost::shared_ptr<ModelLoader> ModelLoader::create()
	{
		return boost::shared_ptr<ModelLoader>(new ModelLoader());
	}

	ModelLoader::ModelLoader()
	{
		LOG_VERBOSE << "ModelLoader constructor";
	}

	ModelLoader::~ModelLoader()
	{
		LOG_VERBOSE << "ModelLoader destructor";
	}

	namespace
	{
		struct Vert
		{
			Vert(const Vec3& vP, const Vec3& vN, const Vec3& vT, const Vec3& vBT, const Vec2& vUV0, const Vec2& vUV1)
				: vPos(vP)
				, vNormal(vN)
				, vTangent(vT)
				, vBitangent(vBT)
				, vTexCoord0(vUV0)
				, vTexCoord1(vUV1) {}

			Vec3 vPos;
			Vec3 vNormal;
			Vec3 vTangent;
			Vec3 vBitangent;
			Vec2 vTexCoord0;
			Vec2 vTexCoord1;
		};

		Mat4 convertMatrix(const aiMatrix4x4& aiMat)
		{
			Mat4 mMat;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					mMat[i][j] = aiMat[j][i];

			return mMat;
		}

		Vert buildVertex(aiMesh* pMesh, unsigned int iIndex)
		{
			auto aiPos = pMesh->mVertices[iIndex];
			Vec3 vPos(aiPos[0], aiPos[1], aiPos[2]);

			Vec3 vNormal(0.0, 0.0, 0.0);
			if (pMesh->HasNormals())
			{
				auto aiNormal = pMesh->mNormals[iIndex];
				vNormal = Vec3(aiNormal[0], aiNormal[1], aiNormal[2]);
			}

			Vec3 vTangent(0.0, 0.0, 0.0);
			Vec3 vBitangent(0.0, 0.0, 0.0);
			if (pMesh->HasTangentsAndBitangents())
			{
				auto aiTangent = pMesh->mTangents[iIndex];
				auto aiBitangent = pMesh->mBitangents[iIndex];
				vTangent = Vec3(aiTangent[0], aiTangent[1], aiTangent[2]);
				vBitangent = Vec3(aiBitangent[0], aiBitangent[1], aiBitangent[2]);
			}

			Vec2 vTexCoord0(0.0, 0.0);
			if (pMesh->HasTextureCoords(0))
			{
				auto aiTexCoord = pMesh->mTextureCoords[0][iIndex];
				vTexCoord0 = Vec2(aiTexCoord[0], aiTexCoord[1]);
			}

			Vec2 vTexCoord1(0.0, 0.0);
			if (pMesh->HasTextureCoords(1))
			{
				auto aiTexCoord = pMesh->mTextureCoords[1][iIndex];
				vTexCoord1 = Vec2(aiTexCoord[0], aiTexCoord[1]);
			}

			return Vert(vPos, vNormal, vTangent, vBitangent, vTexCoord0, vTexCoord1);
		}

		boost::shared_ptr<Visual> buildVisual(const aiScene* pScene, aiMesh* pMesh)
		{
			// Create vertex list that always uses following 6 attributes - will be partially filled in depending on what's available in aiMesh
			auto spVL = VertexLayout::create();
			spVL->add(VertexAttribute("position", 0, 3, TYPE_FLOAT, 0));
			spVL->add(VertexAttribute("normal", 1, 3, TYPE_FLOAT, 3*sizeof(float)));
			spVL->add(VertexAttribute("tangent", 2, 3, TYPE_FLOAT, 6*sizeof(float)));
			spVL->add(VertexAttribute("bitangent", 3, 3, TYPE_FLOAT, 9*sizeof(float)));
			spVL->add(VertexAttribute("texcoord0", 4, 2, TYPE_FLOAT, 12*sizeof(float), true));
			spVL->add(VertexAttribute("texcoord1", 5, 2, TYPE_FLOAT, 14*sizeof(float), true));
			auto spVertexList = boost::shared_ptr<VertexList<Vert>>(new VertexList<Vert>(spVL));

			// Get vertices from aiMesh
			for (unsigned int i = 0; i < pMesh->mNumVertices; ++i)
				spVertexList->addVertex( buildVertex(pMesh, i) );

			// Get indices from aiMesh
			for (unsigned int i = 0; i < pMesh->mNumFaces; ++i)
			{
				if (pMesh->mFaces[i].mNumIndices != 3)
					LOG_ERROR << __FUNCTION__": Adding non-triangle poly!" << std::endl;

				for (unsigned int j = 0; j < pMesh->mFaces[i].mNumIndices; ++j)
				{
					spVertexList->addIndex(pMesh->mFaces[i].mIndices[j]);
				}
			}

			// Get material properties and textures from aiMesh
			if (pScene->HasMaterials())
			{
				// Get diffuse texture
				aiString diffuseTexturePath;
				pScene->mMaterials[pMesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseTexturePath);

				fs::path fsDiffuseTex(diffuseTexturePath.C_Str());
				if (fs::exists(fsDiffuseTex))
					LOG_INFO << "Found diffuse tex!" << std::endl;
			}

			auto spVertexShader = ShaderObject::load("../Data/Shaders/Default.vert");
			auto spFragmentShader = ShaderObject::load("../Data/Shaders/ColourSimple.frag");

			std::vector<boost::shared_ptr<ShaderObject>> aspShaders;
			aspShaders.push_back(spVertexShader);
			aspShaders.push_back(spFragmentShader);

			auto spShaderPipeline = ShaderPipeline::create("DefaultPipeline", aspShaders);

			auto spShader = spShaderPipeline->createInstance();
			auto spMaterial = Material::create(spShader, null_ptr, null_ptr); // Skip texture for now
			auto spStaticGeometry = StaticGeometry::create(spVertexList, Geometry::TRIANGLES);

			return Visual::create(spStaticGeometry, spMaterial);
		}

		void buildModel(const aiScene* pScene, aiNode* pNode, const boost::shared_ptr<Node> spParentNode)
		{
			auto spNode = Node::create();
			spNode->setName(pNode->mName.C_Str());
			spNode->modifyLocalTransform() = convertMatrix(pNode->mTransformation);

			for (unsigned int i = 0; i < pNode->mNumMeshes; ++i)
			{
				auto spVisual = buildVisual(pScene, pScene->mMeshes[pNode->mMeshes[i]]);
				spVisual->setName(spNode->getName() + "Visual");
				spNode->addChild(spVisual);
			}

			spParentNode->addChild(spNode);

			for (unsigned int i = 0; i < pNode->mNumChildren; ++i)
				buildModel(pScene, pNode->mChildren[i], spNode);
		}

	}

	boost::shared_ptr<Node> ModelLoader::load(const fs::path& fsPath)
	{
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << fsPath.string() << " - doesn't exist";
			assert(false);
		}

		Assimp::Importer i;
		const aiScene* scene = i.ReadFile(fsPath.string(),
										  aiProcess_CalcTangentSpace	  |
										  aiProcess_Triangulate			  |
										  aiProcess_JoinIdenticalVertices |
										  aiProcess_SortByPType);

		if (!scene)
		{
			LOG_ERROR << "Failed to import model: " << i.GetErrorString() << std::endl;
			assert(false);
		}

		auto spNode = Node::create();
		buildModel(scene, scene->mRootNode, spNode);

		return spNode;
	}

} }