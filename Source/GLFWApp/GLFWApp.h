#pragma once

#include <string>

struct GLFWwindow;

namespace baselib
{
	class GLFWApp
	{
	public:
		//! Constructor.
		GLFWApp();
		//! Destructor.
		virtual ~GLFWApp();

		//! Create the main GLFW window, OpenGL context and associate the context with the window.
		void init();
		//! Destroy the window and terminate GLFW.
		void destroy();

		//! Process all application events. (i.e. key presses, mouse clicks, window resize etc.)
		void processEvents();
		//! Swap the front and back buffers.
		void swapBuffers();

		//! Returns false if the app should be terminated.
		bool isAppRunning() const { return m_bAppRunning; }
		//! Returns true if the window and context was successfully created.
		bool isInitialized() const { return m_bInitialized; }
		//! Return time elapsed from application start.
		double GetTime() const;

		//! Set window title text.
		void setWindowTitle(const std::string& s) { m_sWindowTitle = s; }
		//! Getter for setWindowTitle().
		std::string getWindowTitle() const { return m_sWindowTitle; }

		//! Set the window width.
		void setWidth(int i) { m_iWidth = i; }
		//! Getter for setWidth().
		int getWidth() const { return m_iWidth; }

		//! Set the window height.
		void setHeight(int i) { m_iHeight = i; }
		//! Getter for setHeight().
		int getHeight() const { return m_iHeight; }

		//! Set to full screen or windowed mode.
		void setFullScreen(bool b) { m_bFullscreen = b; }
		//! Getter for setFullScreen().
		bool getFullScreen() const { return m_bFullscreen; }

		//! Set the major OpenGL context version. Has to be set before start() is called.
		void setMajorVersion(int i) { m_iMajorVersion = i; }
		//! Getter for setMajorVersion().
		int getMajorVersion() const { return m_iMajorVersion; }

		//! Set the minor OpenGL context version. Has to be set before start() is called.
		void setMinorVersion(int i) { m_iMinorVersion = i; }
		//! Getter for setMinorVersion().
		int getMinorVersion() const { return m_iMinorVersion; }

	private:
		//! Set the app "running" state. When set to false the main update loop will terminate.
		void setAppRunning(bool b) { m_bAppRunning = b; }
		//! Set the app initialized state.
		void setInitialized(bool b) { m_bInitialized = b; }

		void keyEvent(int iKey, int iAction);
		void mouseMove();
		void mouseButton(int iButton, int iAction);
		void mouseScroll(double dScroll);
		void mouseEnter(int iEnter);

		//! Called after window and OpenGL context was successfully created. Derived app should do initialization here.
		virtual void onInit() {}
		//! Called before window and OpenGL context is destroyed. Derived app should do cleanup here before window is destroyed.
		virtual void onDestroy() {}

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

		// TODO: Implement window events
		//! Called when window is moved.
		virtual void onWindowMove(int iX, int iY) {}
		//! Called when window is resized.
		virtual void onWindowResize(int iWidth, int iHeight) {}
		//! Called when window is closed.
		virtual void onWindowClose() {}
		//! Called when window is refreshed.
		virtual void onWindowRefresh() {}


		bool m_bAppRunning;			 //!< While true the main update loop will execute. When set to false the main loop terminates and the app closes.
		bool m_bInitialized;		 //!< True after the main window and OpenGL context was successfully created. 
		std::string m_sWindowTitle;	 //!< The current window title.
		int m_iWidth;				 //!< Window width in pixels.
		int m_iHeight;				 //!< Window height in pixels.
		bool m_bFullscreen;			 //!< True when in full screen mode and false when in windowed mode.
		int m_iMajorVersion;		 //!< The major version of the OpenGL context. May not be the actual version of context that was created - could fall back to older version.
		int m_iMinorVersion;		 //!< The minor version of the OpenGL context. May not be the actual version of context that was created - could fall back to older version.
		GLFWwindow* m_pWindow;		 //!< The GLFW window.

		int m_iMouseX;				 //!< The current X coordinate of the mouse in pixels relative to the top left corner of the window.
		int m_iMouseY;				 //!< The current Y coordinate of the mouse in pixels relative to the top left corner of the window.
		int m_iMouseXPrev;			 //!< The previous X coordinate of the mouse in pixels relative to the top left corner of the window.
		int m_iMouseYPrev;			 //!< The previous Y coordinate of the mouse in pixels relative to the top left corner of the window.
	};
}