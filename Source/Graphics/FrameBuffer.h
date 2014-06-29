#pragma once

#include <boost/shared_ptr.hpp>

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
			//! Creates and returns a frame buffer object.
			static boost::shared_ptr<FrameBuffer> create();
			
			//! Destructor.
			virtual ~FrameBuffer();

			//! Bind frame buffer.
			void bind();

			//! Get frame buffer ID.
			unsigned int getID() const { return m_uID; }

		protected:
			//! Protected constructor - must be constructed with static create().
			FrameBuffer(unsigned int uID);

		private:
			unsigned int m_uID; //!< Framebuffer object ID.
		};
	}
}