#include "Material.h"

#include <Logging/Log.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <GL/glew.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<Material> Material::create(const boost::shared_ptr<Shader>& spShader, const boost::shared_ptr<Texture>& spTexture, const boost::shared_ptr<RenderState>& spRenderState)
	{
		return boost::shared_ptr<Material>(new Material(spShader, spTexture, spRenderState));
	}

	Material::Material( const boost::shared_ptr<Shader>& spShader, const boost::shared_ptr<Texture>& spTexture, const boost::shared_ptr<RenderState>& spRenderState)
		: m_spShader(spShader)
		, m_spTexture(spTexture)
		, m_spRenderState(spRenderState)
	{
		LOG_VERBOSE << "Material constructor";
	}

	Material::~Material()
	{
		LOG_VERBOSE << "Material destructor";
	}

	void Material::bind()
	{
		if (m_spShader)
		{
			m_spShader->bind();
			glUniform1i(glGetUniformLocation(m_spShader->getID(), "sTestTexture"), 0);
		}

		if (m_spTexture)
		{
			m_spTexture->bind();
		}
	}

} }