#pragma once

#include <memory>
#include <string>
#include <map>

#include <Core/ResourceCache.h>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/filesystem.hpp>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/algorithm.hpp>

namespace fs = boost::filesystem;

namespace baselib
{
	namespace graphics
	{
		class Image;
		class ShaderObject;
		class Node;
	}
}

namespace baselib
{
	/*! @brief Loader implementation for a specific type of resource.
	 *
	 */
	template <class ResourceType>
	class LoaderImp
	{
	public:
		std::shared_ptr<ResourceType> load(const fs::path& phFilename)
		{
			std::string sCanonicalPath = fs::canonical(phFilename).string();
			if (auto sp = getResource(sCanonicalPath))
				return sp;

			auto sp = ResourceType::load(sCanonicalPath);
			addResource(sCanonicalPath, sp);
			return sp;
		}

		//! Add a resource to the cache.
		void addResource(const std::string& sName, const std::weak_ptr<ResourceType>& wpResource)
		{
			m_ResourceMap[sName] = wpResource;
		}

		//! Get a resource from the cache.
		std::shared_ptr<ResourceType> getResource(const std::string& sName)
		{
			auto iter = m_ResourceMap.find(sName);
			if (iter != m_ResourceMap.end())
			{
				LOG_VERBOSE << sName << " resource is cached";
				if (auto sp = iter->second.lock())
				{
					LOG_VERBOSE << "Returning cached resource " << sName;
					return sp;
				}
				else
				{
					LOG_VERBOSE << sName << " resource doesn't exist anymore. Removing reference.";
					m_ResourceMap.erase(iter);
				}
			}
			return null_ptr;
		}

	private:
		boost::unordered_map<std::string, std::weak_ptr<ResourceType>> m_ResourceMap;

	};

	/*! @brief Resource manager does all loading and caching of resource i.e. textures, shaders, sounds etc.
	 *
	 */
	class ResourceLoader
	{
	public:
		//! Constructor.
		ResourceLoader();
		//! Destructor.
		virtual ~ResourceLoader();

	private:

	};
}