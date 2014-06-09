#pragma once

#include <string>

namespace baselib 
{
	namespace graphics
	{
		class ShaderPipeline
		{
		public:
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
			//! Private constructor - must be created using ShaderManager.
			friend class ShaderManager;
			ShaderPipeline(const std::string& sName, unsigned int uID);

			std::string m_sName;  //!< Pipeline name.
			unsigned int m_uID;	  //!< Uniqe ID.
		};
	}
}