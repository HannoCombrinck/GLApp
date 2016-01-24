#pragma once

#include <memory>

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
		void prepareShader(const std::shared_ptr<Shader>& spShader);
	}
}