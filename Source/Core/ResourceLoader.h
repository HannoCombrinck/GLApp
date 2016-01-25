#pragma once

#include <memory>
#include <string>
#include <map>

#include <Core/NullPtr.h>
#include <Core/Resource.h>
#include <Core/ObjectCache.h>

#include <boost/unordered_map.hpp>

namespace baselib
{
	/*! @brief Resource loader does all loading and caching of resource i.e. textures, shaders, sounds etc.
	 *
	 */
	class ResourceLoader
	{
	public:
		//! Create a resource loader
		static std::shared_ptr<ResourceLoader> create()
		{
			return std::shared_ptr<ResourceLoader>(new ResourceLoader());
		}

		//! Get the cached resource if it exists otherwise load and cache it.
		template <class T>
		std::shared_ptr<T> load(const fs::path& phFilename)
		{
			std::string sCanonicalPath = fs::canonical(phFilename).string();
			if (auto sp = m_Cache.get(sCanonicalPath))
				return std::dynamic_pointer_cast<T>(sp);

			auto sp = T::load(sCanonicalPath);
			sp->setFilename(sCanonicalPath);
			m_Cache.add(sCanonicalPath, sp);
			return std::dynamic_pointer_cast<T>(sp);
		}

	private:
		//! Protected constructor - must be constructed by static Create().
		ResourceLoader() {}

		ObjectCache<Resource> m_Cache;

	};
}