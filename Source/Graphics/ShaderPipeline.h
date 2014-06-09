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

			//! Get pipeline name.
			std::string getName() const { return m_sName; }
			//! Get pipeline ID.
			unsigned int getID() const { return m_uID; }

		private:
			friend class ShaderManager;
			//! Private constructor - must be created using ShaderManager.
			ShaderPipeline(const std::string& sName, unsigned int uID);

			std::string m_sName;  //!< Pipeline name.
			unsigned int m_uID;	  //!< Shader pipeline ID.
		};
	}
}