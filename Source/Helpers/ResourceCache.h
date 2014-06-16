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
		ResourceCache() { LOG_VERBOSE << "ResourceCache constructor"; }
		//! Destructor.
		virtual ~ResourceCache() { LOG_VERBOSE << "ResourceCache destructor"; }

		//! Add a resource to the cache.
		void add(const std::string& sName, const boost::shared_ptr<Resource>& spResource)
		{

		}

		//! Get a resource from the cache.
		boost::shared_ptr<Resource> get(const std::string& sName)
		{
			return null_ptr;
		}

	private:
		boost::unordered_map<std::string, boost::weak_ptr<Resource>> m_aResourceMap; //!< Map with weak references to all created resources.
		
	};
}