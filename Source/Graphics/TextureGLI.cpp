#include "TextureGLI.h"

#include <Logging/Log.h>
#include <GL/glew.h>

#include <Math/Math.h>

#include <gli/texture.hpp>
#include <gli/save.hpp>
#include <gli/load.hpp>
#include <gli/gl.hpp>

namespace baselib { namespace graphics {

	unsigned int TextureGLI::m_uCurrentlyBound = ~0;
	unsigned int TextureGLI::m_uActiveUnit = ~0;

	namespace
	{
		// Convert from GLI target type to TextureGLI::TextureType
		TextureGLI::TextureType gliToType(gli::gl::target uTarget)
		{
			switch (uTarget)
			{
				case gli::gl::TARGET_1D:		 return TextureGLI::TEXTURE_1D; break;
				case gli::gl::TARGET_1D_ARRAY:	 return TextureGLI::TEXTURE_1D_ARRAY; break;
				case gli::gl::TARGET_2D:		 return TextureGLI::TEXTURE_2D; break;
				case gli::gl::TARGET_CUBE:		 return TextureGLI::TEXTURE_CUBE_MAP; break;
				case gli::gl::TARGET_2D_ARRAY:	 return TextureGLI::TEXTURE_2D_ARRAY; break;
				case gli::gl::TARGET_3D:		 return TextureGLI::TEXTURE_3D; break;
				case gli::gl::TARGET_CUBE_ARRAY: return TextureGLI::TEXTURE_CUBE_MAP_ARRAY; break;
				default: LOG_ERROR << "Undefined texture target"; assert(0); return TextureGLI::TEXTURE_UNDEFINED; break;
			}
		}

		// Convert from TextureGLI::TextureType to OpenGL type
		unsigned int typeToGLType(TextureGLI::TextureType eType)
		{
			switch (eType)
			{
				case TextureGLI::TEXTURE_1D:			 return GL_TEXTURE_1D; break;
				case TextureGLI::TEXTURE_1D_ARRAY:		 return GL_TEXTURE_1D_ARRAY; break;
				case TextureGLI::TEXTURE_2D:			 return GL_TEXTURE_2D; break;
				case TextureGLI::TEXTURE_CUBE_MAP:		 return GL_TEXTURE_CUBE_MAP; break;
				case TextureGLI::TEXTURE_2D_ARRAY:		 return GL_TEXTURE_2D_ARRAY; break;
				case TextureGLI::TEXTURE_3D:			 return GL_TEXTURE_3D; break;
				case TextureGLI::TEXTURE_CUBE_MAP_ARRAY: return GL_TEXTURE_CUBE_MAP_ARRAY; break;
				default: LOG_ERROR << "Undefined texture type"; assert(0); return 0; break;
			}
		}
	}

	// Use GLI library to load texture and convert to custom types and enums
	std::shared_ptr<TextureGLI> TextureGLI::load(const fs::path& fsPath)
	{
		// Check if image file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find image " << fsPath;
			assert(false);
		}
		
		gli::texture gliTex = gli::load(fsPath.string());
		if (gliTex.empty())
		{
			LOG_ERROR << "Error loading image " << fsPath;
			assert(false);
		}
		
		gli::gl GL;
		auto gliTexFormat = GL.translate(gliTex.format());
		auto gliTexTarget = GL.translate(gliTex.target());

		auto uMipLevels = gliTex.levels();
		auto uFaces = gliTex.faces();
		auto uArraySlices = gliTex.layers();
		auto vDimensions = Vec3(gliTex.dimensions());
		auto uFacesTotal = uArraySlices * uFaces;

		unsigned int uID;
		glGenTextures(1, &uID);
		glBindTexture(gliTexTarget, uID);

		auto eTexType = gliToType(gliTexTarget); 
		auto spTexture = std::shared_ptr<TextureGLI>(new TextureGLI(uID, eTexType, uArraySlices, uFaces, uMipLevels));
		auto& aImages = spTexture->modifyImageData(); 
		// TODO: populate aImages

		glTexParameteri(gliTexTarget, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(gliTexTarget, GL_TEXTURE_MAX_LEVEL, int(uMipLevels - 1));
		glTexParameteri(gliTexTarget, GL_TEXTURE_SWIZZLE_R, gliTexFormat.Swizzle[0]);
		glTexParameteri(gliTexTarget, GL_TEXTURE_SWIZZLE_G, gliTexFormat.Swizzle[1]);
		glTexParameteri(gliTexTarget, GL_TEXTURE_SWIZZLE_B, gliTexFormat.Swizzle[2]);
		glTexParameteri(gliTexTarget, GL_TEXTURE_SWIZZLE_A, gliTexFormat.Swizzle[3]);

		switch (gliTex.target())
		{
		case gli::TARGET_1D:
			glTexStorage1D(gliTexTarget, int(uMipLevels), gliTexFormat.Internal, int(vDimensions.x));
			break;

		case gli::TARGET_1D_ARRAY:
		case gli::TARGET_2D:
		case gli::TARGET_CUBE:
			glTexStorage2D(gliTexTarget, int(uMipLevels), gliTexFormat.Internal,
						   int(vDimensions.x), gliTex.target() == gli::TARGET_2D ? int(vDimensions.y) : int(uFacesTotal));
			break;

		case gli::TARGET_2D_ARRAY:
		case gli::TARGET_3D:
		case gli::TARGET_CUBE_ARRAY:
			glTexStorage3D(gliTexTarget, int(uMipLevels), gliTexFormat.Internal,
						   int(vDimensions.x), int(vDimensions.y), gliTex.target() == gli::TARGET_3D ? int(vDimensions.z) : int(uFacesTotal));
			break;
		default: assert(0); break;
		}

		// TODO: add create and populate ImageData array here for local storage of textures
		for (auto uArraySlice = 0U; uArraySlice < uArraySlices; ++uArraySlice)
		{
			for (auto uFace = 0U; uFace < uFaces; ++uFace)
			{
				for (auto uMipLevel = 0U; uMipLevel < uMipLevels; ++uMipLevel)
				{
					auto vLevelDimensions = Vec3(gliTex.dimensions(uMipLevel));

					if (gli::is_target_cube(gliTex.target()))
						gliTexTarget = gli::gl::target(GL_TEXTURE_CUBE_MAP_POSITIVE_X + uFace);

					switch (gliTex.target())
					{
					case gli::TARGET_1D:
						if (gli::is_compressed(gliTex.format()))
						{
							glCompressedTexSubImage1D(gliTexTarget, int(uMipLevel), 0, int(vLevelDimensions.x), 
													  gliTexFormat.Internal, int(gliTex.size(uMipLevel)), 
													  gliTex.data(uArraySlice, uFace, uMipLevel));
						}
						else
						{
							glTexSubImage1D(gliTexTarget, int(uMipLevel), 0, int(vLevelDimensions.x), 
										    gliTexFormat.Internal, gliTexFormat.Type,
											gliTex.data(uArraySlice, uFace, uMipLevel));
						}
						break;

					case gli::TARGET_1D_ARRAY:
					case gli::TARGET_2D:
					case gli::TARGET_CUBE:
						if (gli::is_compressed(gliTex.format()))
						{
							glCompressedTexSubImage2D(gliTexTarget, int(uMipLevel), 0, 0,
													  int(vLevelDimensions.x), 
													  gliTex.target() == gli::TARGET_1D_ARRAY ? int(uArraySlice) : int(vLevelDimensions.y),
													  gliTexFormat.Internal, int(gliTex.size(uMipLevel)),
													  gliTex.data(uArraySlice, uFace, uMipLevel));
						}
						else
						{
							glTexSubImage2D(gliTexTarget, int(uMipLevel), 0, 0, 
											int(vLevelDimensions.x), gliTex.target() == gli::TARGET_1D_ARRAY ? int(uArraySlice) : int(vLevelDimensions.y),
											gliTexFormat.External, gliTexFormat.Type, gliTex.data(uArraySlice, uFace, uMipLevel));
						}
						break;

					case gli::TARGET_2D_ARRAY:
					case gli::TARGET_3D:
					case gli::TARGET_CUBE_ARRAY:
						if (gli::is_compressed(gliTex.format()))
						{
							glCompressedTexSubImage3D(gliTexTarget, int(uMipLevel), 0, 0, 0,
													  int(vLevelDimensions.x), int(vLevelDimensions.y), gliTex.target() == gli::TARGET_3D ? int(vLevelDimensions.z) : int(uArraySlice),
													  gliTexFormat.Internal, int(gliTex.size(uArraySlice)),
													  gliTex.data(uArraySlice, uFace, uMipLevel));
						}
						else
						{
							glTexSubImage3D(gliTexTarget, int(uMipLevel), 0, 0, 0,
											int(vLevelDimensions.x), int(vLevelDimensions.y), gliTex.target() == gli::TARGET_3D ? int(vLevelDimensions.z) : int(uArraySlice),
											gliTexFormat.External, gliTexFormat.Type, gliTex.data(uArraySlice, uFace, uMipLevel));
						}
						break;

					default:
						LOG_ERROR << "Unknown texture type";
						assert(false);
						break;
					}

				}
			}
		}
		
		return spTexture;
	}

	//std::shared_ptr<TextureGLI> TextureGLI::create()
	
	TextureGLI::TextureGLI(unsigned int uID, TextureType eType, unsigned int uArraySlices, unsigned int uFaces, unsigned int uMipLevels)
		: m_uID(uID)
		, m_eType(eType)
		, m_uArraySlices(uArraySlices)
		, m_uFaces(uFaces)
		, m_uMipLevels(uMipLevels)
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

		glBindTexture(typeToGLType(m_eType), m_uID);
		m_uCurrentlyBound = m_uID;
	}

} }