#pragma once

#include <string>
#include <vector>
#include <memory>

namespace baselib 
{
	namespace graphics
	{
		class Shader;
		class ShaderObject;
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
		class ShaderPipeline : public std::enable_shared_from_this<ShaderPipeline>
		{
		public:
			//! Creates and links a shader pipeline with the given shader objects.
			static std::shared_ptr<ShaderPipeline> create(const std::string& sName, const std::vector<std::shared_ptr<ShaderObject>>& aspShaderObjects);

			//! Destructor.
			virtual ~ShaderPipeline();

			//! Create a Shader instance based on this pipeline.
			std::shared_ptr<Shader> createInstance();

			//! Get pipeline name.
			std::string getName() const { return m_sName; }
			//! Get pipeline ID.
			unsigned int getID() const { return m_uID; }

		protected:
			//! Protected constructors - must be created by static create().
			ShaderPipeline(const std::string& sName, unsigned int uID, const std::vector<std::shared_ptr<ShaderObject>>& aspShaderObjects);

		private:
			std::string m_sName;  //!< Pipeline name.
			unsigned int m_uID;	  //!< Shader pipeline ID.
			std::vector<std::shared_ptr<ShaderObject>> m_aspShaderObjects; //!< The shader objects used to create this pipeline. Only used for debugging.

		};
	}
}