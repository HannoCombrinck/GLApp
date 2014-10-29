#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		class Node;
		class Visual;
		class ShaderPipeline;
	}
}

struct aiScene;
struct aiMesh;
struct aiNode;

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Model loader
		 *
		 */
		class ModelLoader
		{
		public:
			//! Creates a ModelLoader.
			static boost::shared_ptr<ModelLoader> create();

			//! Destructor.
			virtual ~ModelLoader();

			//! Load model from file
			boost::shared_ptr<Node> load(const fs::path& fsPath);

		protected:
			//! Protected constructor - must be created by static create().
			ModelLoader();

		private:
			boost::shared_ptr<Visual> buildVisual(const aiScene* pScene, aiMesh* pMesh);
			void buildModel(const aiScene* pScene, aiNode* pNode, const boost::shared_ptr<Node> spParentNode);

			boost::shared_ptr<ShaderPipeline> m_spShaderPipeline;
		};
	}
}