#include "Material.h"

#include <Logging/Log.h>

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

} }