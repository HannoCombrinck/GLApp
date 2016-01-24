#pragma once

#include <memory>
#include <string>

namespace baselib
{
	namespace graphics
	{
		class Renderer;
		class ShaderPipeline;
		class StaticGeometry;
		class Material;
		class Node;
	}
}

namespace baselib
{
	/*! @brief Resource manager does all loading and caching of resource i.e. textures, shaders, sounds etc.
	 *
	 */
	class ResourceLoader
	{
	public:
		//! Constructor.
		ResourceLoader();
		//! Destructor.
		virtual ~ResourceLoader();

		std::shared_ptr<graphics::Node> getModel(const std::string& sFilename);

	private:
		
	};
}