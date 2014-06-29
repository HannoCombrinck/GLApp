#include "FrameBuffer.h"

#include <Logging/Log.h>
#include <GL/glew.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<FrameBuffer> FrameBuffer::create()
	{
		unsigned int uID;
		glGenFramebuffers(1, &uID);
		auto spFrameBuffer = boost::shared_ptr<FrameBuffer>(new FrameBuffer(uID));
		return spFrameBuffer;
	}

	FrameBuffer::FrameBuffer(unsigned int uID)
		: m_uID(uID)
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
		// Read, write, both
		glBindFramebuffer(GL_FRAMEBUFFER, m_uID);
	}

} }