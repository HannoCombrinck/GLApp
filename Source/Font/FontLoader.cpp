#include "FontLoader.h"

#include <Core/NullPtr.h>
#include <Logging/Log.h>
#include <Font/Font.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace baselib { namespace font {

	namespace
	{
		FT_Library g_FTLib;
	}

	std::shared_ptr<FontLoader> FontLoader::create()
	{
		return std::shared_ptr<FontLoader>(new FontLoader());
	}

	FontLoader::FontLoader()
	{
		LOG_VERBOSE << "FontLoader constructor";
		init();
	}

	FontLoader::~FontLoader()
	{
		LOG_VERBOSE << "FontLoader destructor";
		destroy();
	}

	void FontLoader::init()
	{
		FT_Error ftError = FT_Init_FreeType(&g_FTLib);
		if (ftError)
		{
			LOG_ERROR << "Failed to initialize freetype";
			assert(false);
		}
	}

	void FontLoader::destroy()
	{
		FT_Error ftError = FT_Done_FreeType(g_FTLib);
		if (ftError)
		{
			LOG_ERROR << "Failed to destroy freetype";
			assert(false);
		}
	}

	std::shared_ptr<Font> FontLoader::loadFont(const fs::path& fsPath, const std::shared_ptr<graphics::Renderer>& spRenderer, const Vec2& vAtlasSize)
	{
		// Check if font file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find font file: " << fsPath;
			assert(false);
		}
		std::string sCanonicalPath = fs::canonical(fsPath).string();

		// Load font from file
		FT_Face ftFace;
		FT_Error ftError = FT_New_Face(g_FTLib, sCanonicalPath.c_str(), 0, &ftFace);
		if (ftError == FT_Err_Unknown_File_Format)
		{
			LOG_ERROR << "Unknown font file format: " << fsPath;
			assert(false);
		}
		else if (ftError)
		{
			LOG_ERROR << "Freetype failed to load font: " << fsPath;
			assert(false);
		}

		// Check freetype tutorial on how to use other character maps
		if (!ftFace->charmap)
		{
			LOG_ERROR << "Font doesn't contain Unicode character map";
			assert(false);
		}

		FT_Set_Char_Size(ftFace, 50*64, 0, 100, 0);

		return std::shared_ptr<Font>(new Font(ftFace, spRenderer, vAtlasSize));
	}

} }