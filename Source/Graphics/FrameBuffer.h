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
			//! Creates and returns an empty frame buffer object. 
			static boost::shared_ptr<FrameBuffer> createEmpty();
			
			//! Destructor.
			virtual ~FrameBuffer();

			//! Bind frame buffer.
			void bind();
			//! Bind frame buffer and set colour target.
			void bind(const boost::shared_ptr<Texture>& spColourTarget);

			//! Get frame buffer ID.
			unsigned int getID() const { return m_uID; }

			//! Set the width.
			void setWidth(int iWidth) { m_iWidth = iWidth; }
			//! Get the width.
			int getWidth() const { return m_iWidth; }
			//! Set the height.
			void setHeight(int iHeight) { m_iHeight = iHeight; }
			//! Get the height.
			int getHeight() const { return m_iHeight; }
			//! Set the bits per pixel.
			void setBPP(int iBPP) { m_iBPP = iBPP; }
			//! Get the bits per pixel.
			int getBPP() const { return m_iBPP; }

		protected:
			//! Protected constructors - must be constructed with static create().
			FrameBuffer(unsigned int uID, int iNumTargets, const std::vector<boost::shared_ptr<Texture>>& aspColourTargets, const boost::shared_ptr<Texture>& spDepthTarget);
			FrameBuffer(unsigned int uID);

		private:
			static unsigned int m_uCurrentlyBound;			   //!< Currently bound frame buffer.
			static unsigned int m_uCurrentlyBoundColourTarget; //!< Currently bound colour target.

			unsigned int m_uID; //!< Framebuffer object ID. 0 indicates back buffer.
			int m_iNumTargets;  //!< The number of colour targets attached to the framebuffer. 0 indicates back buffer.
			std::vector<boost::shared_ptr<Texture>> m_aspColourTargets; //!< List of colour target textures.
			boost::shared_ptr<Texture> m_spDepthTarget; //!< Depth texture.

			int m_iWidth;  //!< Width of frame buffer.
			int m_iHeight; //!< Height of frame buffer.
			int m_iBPP;	   //!< Bits per pixel of frame buffer.
		};
	}
}