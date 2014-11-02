#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

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
		class ShaderPipeline : public boost::enable_shared_from_this<ShaderPipeline>
		{
		public:
			//! Creates and links a shader pipeline with the given shader objects.
			static boost::shared_ptr<ShaderPipeline> create(const std::string& sName, const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects);

			//! Destructor.
			virtual ~ShaderPipeline();

			//! Create a Shader instance based on this pipeline.
			boost::shared_ptr<Shader> createInstance();

			//! Get pipeline name.
			std::string getName() const { return m_sName; }
			//! Get pipeline ID.
			unsigned int getID() const { return m_uID; }

		protected:
			//! Protected constructors - must be created by static create().
			ShaderPipeline(const std::string& sName, unsigned int uID);

			/*! @brief Alternative constructor that takes list of of ShaderObjects and keeps them alive along with the pipeline.
			 *
			 *  It is not necessary to keep the shader objects alive to have a working pipeline
			 *  but it's useful for debugging purposes. This constructor should, therefore, only 
			 *  be used in debug configurations. See create() for additional info.
			 */
			ShaderPipeline(const std::string& sName, unsigned int uID, const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects);

		private:
			std::string m_sName;  //!< Pipeline name.
			unsigned int m_uID;	  //!< Shader pipeline ID.
			std::vector<boost::shared_ptr<ShaderObject>> m_aspShaderObjects; //!< The shader objects used to create this pipeline. Only used for debugging.

		};
	}
}