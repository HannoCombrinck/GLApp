#pragma once

#include <GLFWApp/GLFWApp.h>

namespace baselib
{
	class BaseApp : public GLFWApp
	{
	public:
		//! Constructor
		BaseApp();
		//! Destructor
		virtual ~BaseApp();

		//! Start the main update loop in this thread. This call returns when the app is stopped.
		void start();

	private:
		//! Called after window and context gets created. Initialization happens here.
		virtual void onInit();
		//! Called before window and context gets destroyed. Cleanup happens here.
		virtual void onDestroy();
	};
}