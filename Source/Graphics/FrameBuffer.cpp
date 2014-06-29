#include "FrameBuffer.h"

#include <Logging/Log.h>
#include <Graphics/Texture.h>
#include <GL/glew.h>
#include <boost/range/algorithm/for_each.hpp>

namespace baselib { namespace graphics {

	namespace
	{
		void checkValidTargets(const std::vector<boost::shared_ptr<Texture>>& aColourAttachments)
		{
			int iWidth = aColourAttachments[0]->getWidth();
			int iHeight = aColourAttachments[0]->getHeight();
			int iBPP = aColourAttachments[0]->getBPP();

			boost::for_each(aColourAttachments, [iWidth, iHeight, iBPP](const boost::shared_ptr<Texture>& spTexture) {
				if (spTexture->getWidth() != iWidth || spTexture->getHeight() != iHeight)
				{
					LOG_ERROR << "All FrameBuffer target textures must have the same resolution";
					assert(false);
				}
				if (spTexture->getBPP() != iBPP)
				{
					LOG_ERROR << "All FrameBuffer target textures must have the same format";
					assert(false);
				}
			});
		}

		GLenum aColourAttachmentBuffers[] = { GL_COLOR_ATTACHMENT0, 
											  GL_COLOR_ATTACHMENT1, 
											  GL_COLOR_ATTACHMENT2, 
											  GL_COLOR_ATTACHMENT3, 
											  GL_COLOR_ATTACHMENT4, 
											  GL_COLOR_ATTACHMENT5, 
											  GL_COLOR_ATTACHMENT6, 
											  GL_COLOR_ATTACHMENT7, 
											  GL_COLOR_ATTACHMENT8, 
											  GL_COLOR_ATTACHMENT9, 
											  GL_COLOR_ATTACHMENT10, 
											  GL_COLOR_ATTACHMENT11, 
											  GL_COLOR_ATTACHMENT12, 
											  GL_COLOR_ATTACHMENT13, 
											  GL_COLOR_ATTACHMENT14, 
											  GL_COLOR_ATTACHMENT15 };
	}

	boost::shared_ptr<FrameBuffer> FrameBuffer::create()
	{
		return boost::shared_ptr<FrameBuffer>(new FrameBuffer(0, 0));
	}

	boost::shared_ptr<FrameBuffer> FrameBuffer::create(const std::vector<boost::shared_ptr<Texture>>& aspColourTargets, const boost::shared_ptr<Texture>& spDepthTarget)
	{
		checkValidTargets(aspColourTargets);

		// Create and bind frame buffer object
		unsigned int uID;
		glGenFramebuffers(1, &uID);
		glBindFramebuffer(GL_FRAMEBUFFER, uID);

		// Attach colour targets
		int iCount = 0;
		boost::for_each(aspColourTargets, [&iCount](const boost::shared_ptr<Texture>& spTarget) {
			if (spTarget->getType() == Texture::TEXTURE_2D)
			{
				if (iCount >= GL_MAX_COLOR_ATTACHMENTS)
				{
					LOG_ERROR << "Maximum number of colour attachments exceeded";
					assert(false);
				}
				
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + iCount, GL_TEXTURE_2D, spTarget->getID(), 0); // For now always use mip level 0
			}
			else
			{
				LOG_ERROR << "Only 2D targets currently supported";
				assert(false);
			}
		});

		// Attach depth target
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, spDepthTarget->getID(), 0);

		// Check frame buffer object status
		GLenum eReturn = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (eReturn != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERROR << "Frame buffer object incomplete";
			assert(false);
		}

		// Create frame buffer
		auto spFrameBuffer = boost::shared_ptr<FrameBuffer>(new FrameBuffer(uID, aspColourTargets.size()));
		return spFrameBuffer;
	}

	FrameBuffer::FrameBuffer(unsigned int uID, int iNumTargets)
		: m_uID(uID)
		, m_iNumTargets(iNumTargets)
	{
		LOG_VERBOSE << "FrameBuffer constructor";
	}

	FrameBuffer::~FrameBuffer()
	{
		LOG_VERBOSE << "FrameBuffer destructor";
		glDeleteFramebuffers(1, &m_uID);
		m_uID = ~0;
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_uID);
		if (m_iNumTargets > 0)
			glDrawBuffers(m_iNumTargets, aColourAttachmentBuffers);
	}

} }