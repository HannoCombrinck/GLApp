#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include <Helpers/NullPtr.h>

namespace baselib 
{
	namespace graphics
	{
		class Texture;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief FrameBuffer 
		 *
		 */
		class FrameBuffer
		{
		public:
			//! Creates and returns a frame buffer object that binds the default back buffer.
			static boost::shared_ptr<FrameBuffer> create();
			//! Creates and returns a frame buffer object with the given colour targets and depth target.
			static boost::shared_ptr<FrameBuffer> create(const std::vector<boost::shared_ptr<Texture>>& aspColourTargets, const boost::shared_ptr<Texture>& spDepthTarget);
			
			//! Destructor.
			virtual ~FrameBuffer();

			//! Bind frame buffer.
			void bind();

			//! Get frame buffer ID.
			unsigned int getID() const { return m_uID; }

		protected:
			//! Protected constructor - must be constructed with static create().
			FrameBuffer(unsigned int uID, int iNumTargets, const std::vector<boost::shared_ptr<Texture>>& aspColourTargets, const boost::shared_ptr<Texture>& spDepthTarget);

		private:
			unsigned int m_uID; //!< Framebuffer object ID. 0 indicates back buffer.
			int m_iNumTargets;  //!< The number of colour targets attached to the framebuffer. 0 indicates back buffer.
			std::vector<boost::shared_ptr<Texture>> m_aspColourTargets; //!< List of colour target textures.
			boost::shared_ptr<Texture> m_spDepthTarget; //!< Depth texture.
		};
	}
}