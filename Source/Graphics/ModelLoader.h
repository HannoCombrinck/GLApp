#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		class Node;
	}
}

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

		};
	}
}