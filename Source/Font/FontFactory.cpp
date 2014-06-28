#include "FontFactory.h"

#include <Helpers/NullPtr.h>
#include <Logging/Log.h>
#include <Font/Font.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace baselib { namespace font {

	namespace
	{
		FT_Library g_FTLib;
	}

	FontFactory::FontFactory()
	{
		LOG_VERBOSE << "FontFactory constructor";
		init();
	}

	FontFactory::~FontFactory()
	{
		LOG_VERBOSE << "FontFactory destructor";
		destroy();
	}

	void FontFactory::init()
	{
		FT_Error ftError = FT_Init_FreeType(&g_FTLib);
		if (ftError)
		{
			LOG_ERROR << "Failed to initialize freetype";
			assert(false);
		}
	}

	void FontFactory::destroy()
	{
		
	}

	boost::shared_ptr<Font> FontFactory::createFont(const fs::path& fsPath, const Vec2& vAtlasSize)
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

		return boost::shared_ptr<Font>(new Font(ftFace, vAtlasSize));
	}

} }