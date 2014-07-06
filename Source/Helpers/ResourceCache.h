#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <Logging/Log.h>

#include <Helpers/NullPtr.h>

namespace baselib 
{
	/*! @brief A simple templated resource cache.
     *
     */
	template <class Resource>
	class ResourceCache
	{
	public:
		//! Constructor.
		ResourceCache() {}
		//! Destructor.
		virtual ~ResourceCache() {}

		//! Add a resource to the cache.
		void add(const std::string& sName, const boost::weak_ptr<Resource>& wpResource)
		{
			m_ResourceMap[sName] = wpResource;
		}

		//! Get a resource from the cache.
		boost::shared_ptr<Resource> get(const std::string& sName)
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
		boost::unordered_map<std::string, boost::weak_ptr<Resource>> m_ResourceMap; //!< Map with weak references to all created resources.
		
	};
}