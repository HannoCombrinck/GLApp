#include "ModelLoader.h"

#include <Logging/Log.h>
#include <Graphics/Node.h>
//#include <Graphics/Visual.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
		Mat4 convertMatrix(const aiMatrix4x4& aiMat)
		{
			Mat4 mMat;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					mMat[i][j] = aiMat[j][i];

			return mMat;
		}

		void buildModel(aiNode* pNode, const boost::shared_ptr<Node> spParentNode)
		{
			auto spNode = Node::create();
			spNode->setName(pNode->mName.C_Str());
			spNode->modifyLocalTransform() = convertMatrix(pNode->mTransformation);

			if (pNode->mNumMeshes > 0)
			{
				//TODO: Convert aiMeshes to Visuals and add to Node
			}

			spParentNode->addChild(spNode);

			for (unsigned int i = 0; i < pNode->mNumChildren; ++i)
				buildModel(pNode->mChildren[i], spNode);
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
		buildModel(scene->mRootNode, spNode);

		return spNode;
	}

} }