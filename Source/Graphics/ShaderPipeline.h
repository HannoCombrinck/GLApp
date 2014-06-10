#pragma once

#include <string>

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Shader;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A ShaderPipeline is a template to create Shader instances from.
		 *
		 *  Shader instances created from the same pipeline share the same ID
		 *  but have different uniforms, textures etc.
		 */
		class ShaderPipeline
		{
		public:
			friend class ShaderManager;

			//! Destructor.
			~ShaderPipeline();

			//! Create a Shader instance based on this pipeline.
			boost::shared_ptr<Shader> createInstance();

			//! Get pipeline name.
			std::string getName() const { return m_sName; }
			//! Get pipeline ID.
			unsigned int getID() const { return m_uID; }

		protected:
			//! Protected constructor - must be created by ShaderManager.
			ShaderPipeline(const std::string& sName, unsigned int uID);

		private:
			std::string m_sName;  //!< Pipeline name.
			unsigned int m_uID;	  //!< Shader pipeline ID.

		};
	}
}