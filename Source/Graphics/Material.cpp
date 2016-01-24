#include "Material.h"

#include <Logging/Log.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

namespace baselib { namespace graphics {

	std::shared_ptr<Material> Material::create(const std::shared_ptr<Shader>& spShader, const std::shared_ptr<Texture>& spTexture, const std::shared_ptr<RenderState>& spRenderState)
	{
		return std::shared_ptr<Material>(new Material(spShader, spTexture, spRenderState));
	}

	Material::Material( const std::shared_ptr<Shader>& spShader, const std::shared_ptr<Texture>& spTexture, const std::shared_ptr<RenderState>& spRenderState)
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
			m_spShader->setUniform(m_spShader->getUniform("sTestTexture"), 0);
		}

		if (m_spTexture)
		{
			m_spTexture->bind();
		}
	}

} }