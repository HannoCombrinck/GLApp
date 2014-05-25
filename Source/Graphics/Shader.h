#pragma once

#include <string>

namespace baselib 
{
	namespace graphics
	{
		class Shader
		{
		public:
			//! Constructor.
			Shader();
			//! Destructor.
			~Shader();

			//! Set shader ID.
			void setShaderID(unsigned int uID) { m_uID = uID; }
			//! Get shader ID.
			unsigned int getShaderID() const { return m_uID; }

			//! Get attribute index from name.
			int getAttribute(const std::string& sName) const;
			//! Get uniform index from name.
			int getUniform(const std::string& sName) const;
		
		private:
			unsigned int m_uID; //!< Shader program ID.
			
		};
	}
}