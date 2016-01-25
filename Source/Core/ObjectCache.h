#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <memory>
#include <boost/weak_ptr.hpp>
#include <Logging/Log.h>

#include <Core/NullPtr.h>

namespace baselib 
{
	/*! @brief A simple object cache.
     *
     */
	template <class T>
	class ObjectCache
	{
	public:
		//! Constructor.
		ObjectCache() {}
		//! Destructor.
		virtual ~ObjectCache() {}

		//! Add an object to the cache.
		void add(const std::string& sName, const std::weak_ptr<T>& wp)
		{
			m_ObjectMap[sName] = wp;
		}

		//! Get an object from the cache.
		std::shared_ptr<T> get(const std::string& sName)
		{
			auto iter = m_ObjectMap.find(sName);
			if (iter != m_ObjectMap.end())
			{
				LOG_VERBOSE << sName << " object is cached";
				if (auto sp = iter->second.lock())
				{
					LOG_VERBOSE << "Returning cached object " << sName;
					return sp;
				}
				else
				{
					LOG_VERBOSE << sName << " object doesn't exist anymore. Removing reference.";
					m_ObjectMap.erase(iter);
				}
			}
			return null_ptr;
		}

	private:
		boost::unordered_map<std::string, std::weak_ptr<T>> m_ObjectMap; //!< Map with weak references to all created objects.
		
	};
}