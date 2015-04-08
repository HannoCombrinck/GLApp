#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Shader;
	}
}

namespace baselib 
{
	namespace graphics
	{
		//! Bind the shader and upload necessary shader data.
		void prepareShader(const boost::shared_ptr<Shader>& spShader);
	}
}