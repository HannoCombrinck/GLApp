#include "TextureGLI.h"

#include <Logging/Log.h>
#include <GL/glew.h>

namespace baselib { namespace graphics {

	unsigned int TextureGLI::m_uCurrentlyBound = ~0;
	unsigned int TextureGLI::m_uActiveUnit = ~0;

	std::shared_ptr<TextureGLI> TextureGLI::load(const fs::path& fsPath)
	{
		// Check if image file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find image " << fsPath;
			assert(false);
		}

		// TODO

		auto spTexture = std::shared_ptr<TextureGLI>(new TextureGLI(0, TEXTURE_2D));
		return spTexture;
	}

	//std::shared_ptr<TextureGLI> TextureGLI::create()
	
	TextureGLI::TextureGLI(unsigned int uID, TextureType eType)
		: m_uID(uID)
		, m_eType(eType)
	{
		LOG_VERBOSE << "TextureGLI constructor";
	}

	TextureGLI::~TextureGLI()
	{
		LOG_VERBOSE << "TextureGLI destructor";
		glDeleteTextures(1, &m_uID);
		m_uID = ~0;
	}

	void TextureGLI::bind(unsigned int uUnit /*= 0*/)
	{
		if (m_uID == m_uCurrentlyBound)
			return;

		unsigned int uGLUnit = GL_TEXTURE0 + uUnit;
		if (m_uActiveUnit != uGLUnit)
		{
			glActiveTexture(uGLUnit);
			m_uActiveUnit = uGLUnit;
		}

		glBindTexture(GL_TEXTURE_2D, m_uID);
		m_uCurrentlyBound = m_uID;
	}

} }