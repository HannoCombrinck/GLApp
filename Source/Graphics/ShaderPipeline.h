#pragma once

#include <string>

namespace baselib 
{
	namespace graphics
	{
		class ShaderPipeline
		{
		public:
			//! Constructor.
			ShaderPipeline(const std::string& sName, unsigned int uID);
			//! Destructor.
			~ShaderPipeline();

			//! Set pipeline name.
			void setName(const std::string& sName) { m_sName = sName; }
			//! Get pipeline name.
			std::string getName() const { return m_sName; }

			//! Set pipeline ID.
			void setID(unsigned int uID) { m_uID = uID; }
			//! Get pipeline ID.
			unsigned int getID() const { return m_uID; }

		private:
			std::string m_sName;  //!< Pipeline name.
			unsigned int m_uID;	  //!< Uniqe ID.
		};
	}
}