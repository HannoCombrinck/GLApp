#pragma once

#include <GLFWApp/GLFWApp.h>
#include <boost/shared_ptr.hpp>

namespace baselib
{
	namespace graphics
	{
		class Renderer;
	}
}


namespace baselib
{
	/*! @brief Test app
	 *
	 */
	class BaseApp : public GLFWApp
	{
	public:
		//! Constructor.
		BaseApp(int iWidth, int iHeight, bool bFullscreen, int iMajorVersion, int iMinorVersion, const std::string& sWindowTitle);
		//! Destructor.
		virtual ~BaseApp();

		//! Start and run the main update loop in this thread. This function returns when the app is stopped.
		void start();

	private:
		//! Main update function. Called from main loop.
		void update(double dDeltaTime);
		//! Main render function. Called from main loop.
		void render();

		//! Initialization happens here.
		void init();
		//! Cleanup happens here.
		void destroy();

		double m_dCurrentTime;  //!< Current time elapsed since application started.
		double m_dPreviousTime; //!< Time elapsed up to previous update cycle. So time elapsed since previous update = m_dCurrentTime - m_dPreviousTime.

		boost::shared_ptr<graphics::Renderer> m_spRenderer; //!< Main renderer

	};
}