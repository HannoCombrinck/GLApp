#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Shader;
		class Texture;
		class RenderState;
	}
}

namespace baselib 
{
	namespace graphics
	{
		class Material
		{
		public:
			//! Constructor
			Material();
			//! Destructor
			~Material();
		
		private:
			boost::shared_ptr<Shader> m_spShader;			//!< Shader used by this material.
			boost::shared_ptr<Texture> m_spTexture;			//!< Texture used by this material.
			boost::shared_ptr<RenderState> m_spRenderState;	//!< Render state associated with this material.

		};
	}
}