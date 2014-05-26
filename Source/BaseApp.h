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
	class BaseApp : public GLFWApp
	{
	public:
		//! Constructor.
		BaseApp();
		//! Destructor.
		virtual ~BaseApp();

		//! Start and run the main update loop in this thread. This function returns when the app is stopped.
		void start();

	private:
		//! Main update function. Called from main loop.
		void update(double dDeltaTime);
		//! Main render function. Called from main loop.
		void render();

		//! Called after window and context gets created. Initialization happens here.
		virtual void onInit();
		//! Called before window and context gets destroyed. Cleanup happens here.
		virtual void onDestroy();

		double m_dCurrentTime;  //!< Current time elapsed since application started.
		double m_dPreviousTime; //!< Time elapsed up to previous update cycle. So time elapsed since previous update = m_dCurrentTime - m_dPreviousTime.

		boost::shared_ptr<graphics::Renderer> m_spRenderer;
	};
}