#pragma once

#include <Math/Math.h>

#include <string>

#include <boost/signals2.hpp>

struct GLFWwindow;

namespace baselib
{
	/*! @brief Base application that handles windowing, events and OpenGL context.
	 *
	 *  Inherit from this class to create a OpenGL ready window that handles user input.
	 */
	class GLFWApp
	{
	public:
		//! Constructor.
		GLFWApp();
		//! Destructor.
		virtual ~GLFWApp();

		//! Create a window and start the main update loop in this thread. This function returns when the app is stopped.
		void start();
		//! Return time elapsed from application start.
		double GetTime() const;

		//! Set window title text.
		void setWindowTitle(const std::string& s);
		//! Getter for setWindowTitle().
		std::string getWindowTitle() const { return m_sWindowTitle; }

		//! Set window size.
		void setSize(int iWidth, int iHeight);
		//! Get window size.
		void getSize(int& iWidth, int& iHeight) const { iWidth = m_iWidth; iHeight = m_iHeight; }
		
		//! Set to full screen or windowed mode.
		void setFullScreen(bool b);
		//! Getter for setFullScreen().
		bool getFullScreen() const { return m_bFullscreen; }

		//! Set the OpenGL context version. Has to be set before start() is called.
		void setGLVersion(int iMajor, int iMinor) { m_iMajorVersion = iMajor; m_iMinorVersion = iMinor; }
		//! Getter for setGLVersion().
		void getGLVersion(int& iMajor, int& iMinor) { iMajor = m_iMajorVersion; iMinor = m_iMinorVersion; }
		
	private:
		//! Create the main GLFW window, OpenGL context and associate the context with the window.
		void init();
		//! Destroy the window and terminate GLFW.
		void destroy();
		//! Process all application events. (i.e. key presses, mouse clicks, window resize etc.)
		void processEvents();
		//! Swap the front and back buffers.
		void swapBuffers();

		//! Set the app "running" state. When set to false the main update loop will terminate.
		void setAppRunning(bool b) { m_bAppRunning = b; }
		//! Returns false if the app should be terminated.
		bool isAppRunning() const { return m_bAppRunning; }

		//! Key event callback.
		void keyEvent(int iKey, int iAction);
		boost::signals2::scoped_connection m_KeyEventConnection;
		//! Mouse button event callback.
		void mouseButton(int iButton, int iAction);
		boost::signals2::scoped_connection m_MouseButtonConnection;
		//! Mouse enter/exit event callback.
		void mouseEnter(int iEnter);
		boost::signals2::scoped_connection m_MouseEnterConnection;
		//! Mouse wheel scroll event callback.
		void mouseScroll(double dScroll);
		boost::signals2::scoped_connection m_MouseScrollConnection;
		//! Mouse move event callback.		
		void mouseMove();
		//! Window move event callback.
		void windowMove(int iX, int iY);
		boost::signals2::scoped_connection m_WindowMoveConnection;
		//! Window resize event callback.
		void windowResize(int iWidth, int iHeight);
		boost::signals2::scoped_connection m_WindowResizeConnection;
		//! Window frame buffer resize.
		void windowFrameBufferResize(int iWidth, int iHeight);
		boost::signals2::scoped_connection m_WindowFrameBufferResizeConnection;
		//! Window refresh event callback.
		void windowRefresh();
		boost::signals2::scoped_connection m_WindowRefreshConnection;
		//! Window close event callback.
		void windowClose();
		boost::signals2::scoped_connection m_WindowCloseConnection;

		//! Called after window and OpenGL context creation to allow for derived app resrouce creation
		virtual void onInit() {}
		//! Called before window destruction to allow for derived app resource cleanup
		virtual void onDestroy() {}
		//! Update called from main loop
		virtual void onUpdate(double dDeltaTime) {}
		//! Render called from main loop
		virtual void onRender() {}

		//! Called when a key is pressed.
		virtual void onKeyPress(int iKey) {}
		//! Called when a key is released.
		virtual void onKeyRelease(int iKey) {}
		//! Called when the mouse position changes with absolute mouse coordinates.
		virtual void onMouseMove(int iX, int iY) {}
		//! Called when the mouse position changes with change in mouse coordinates. (e.g. mouse moved 2 pixels to the left)
		virtual void onMouseMoveRel(int iDX, int iDY) {}
		//! Called when left mouse button is pressed.
		virtual void onMouseLeftClick(int iX, int iY) {}
		//! Called when left mouse button is released.
		virtual void onMouseLeftRelease(int iX, int iY) {}
		//! Called when right mouse button is pressed.
		virtual void onMouseRightClick(int iX, int iY) {}
		//! Called when right mouse button is released.
		virtual void onMouseRightRelease(int iX, int iY) {}
		//! Called when middle mouse button is pressed.
		virtual void onMouseMiddleClick(int iX, int iY) {}
		//! Called when middle mouse button is released.
		virtual void onMouseMiddleRelease(int iX, int iY) {}
		//! Called when mouse wheel is moved. dScroll is positive when scrolling up and negative when scrolling down.
		virtual void onMouseScroll(double dScroll) {}
		//! Called when the mouse enters the window.
		virtual void onMouseEnter() {}
		//! Called when the mouse exits the window.
		virtual void onMouseExit() {}
		//! Called when window is moved.
		virtual void onWindowMove(int iX, int iY) {}
		//! Called when window is resized.
		virtual void onWindowResize(int iWidth, int iHeight) {}
		//! Called when window's frame buffer is resized.
		virtual void onWindowFrameBufferResize(int iWidth, int iHeight) {}
		//! Called when window is closed.
		virtual void onWindowClose() {}
		//! Called when window is refreshed.
		virtual void onWindowRefresh() {}

		bool m_bAppRunning;			 //!< While true the main update loop will execute. When set to false the main loop terminates and the app closes.
		GLFWwindow* m_pWindow;		 //!< The GLFW window.

		int m_iMouseX;				 //!< The current X coordinate of the mouse in pixels relative to the top left corner of the window.
		int m_iMouseY;				 //!< The current Y coordinate of the mouse in pixels relative to the top left corner of the window.
		int m_iMouseXPrev;			 //!< The previous X coordinate of the mouse in pixels relative to the top left corner of the window.
		int m_iMouseYPrev;			 //!< The previous Y coordinate of the mouse in pixels relative to the top left corner of the window.

		double m_dCurrentTime;		 //!< Current time elapsed since application started.
		double m_dPreviousTime;		 //!< Time elapsed up to previous update cycle. So time elapsed since previous update = m_dCurrentTime - m_dPreviousTime.

		int m_iWidth;				 //!< Current window width
		int m_iHeight;				 //!< Current window height
		bool m_bFullscreen;			 //!< True if in fullscreen mode, false for windowed mode
		int m_iMajorVersion;		 //!< OpenGL major version
		int m_iMinorVersion;		 //!< OpenGL minor version
		std::string m_sWindowTitle;  //!< Window title string
	};
}