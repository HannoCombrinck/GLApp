#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib
{
	/*! brief Resource base.
	 *
	 */
	class Resource
	{
	public:
		//! Constructor.
		Resource() : m_phFilename("NA") {}
		//! Destructor.
		virtual ~Resource() {}
	
		//! Set resource filename
		void setFilename(const fs::path& phFilename) { m_phFilename = phFilename; }
		//! Get resource filename
		const fs::path& getFilename() const { return m_phFilename; }

	private:
		fs::path m_phFilename; //!< Resource filename
	
	};
}
