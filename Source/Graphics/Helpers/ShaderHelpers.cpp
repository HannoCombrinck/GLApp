#include "ShaderHelpers.h"

#include <Graphics/Shader.h>

namespace baselib { namespace graphics {

	void prepareShader(const boost::shared_ptr<Shader>& spShader)
	{
		spShader->bind();
	}

} }