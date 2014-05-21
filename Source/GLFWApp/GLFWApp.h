#pragma once

#include <string>

struct GLFWwindow;

namespace baselib
{
	class GLFWApp
	{
	public:
		GLFWApp();
		virtual ~GLFWApp();

		void start();
		void destroy();

		void processEvents();
		void swapBuffers();

		void setAppRunning(bool b) { m_bAppRunning = b; }
		bool isAppRunning() const { return m_bAppRunning; }

		void setWindowTitle(const std::string& s) { m_sWindowTitle = s; }
		std::string getWindowTitle() const { return m_sWindowTitle; }

		void setWidth(int i) { m_iWidth = i; }
		int getWidth() const { return m_iWidth; }

		void setHeight(int i) { m_iHeight = i; }
		int getHeight() const { return m_iHeight; }

		void setFullScreen(bool b) { m_bFullscreen = b; }
		bool getFullScreen() const { return m_bFullscreen; }

		void setMajorVersion(int i) { m_iMajorVersion = i; }
		int getMajorVersion() const { return m_iMajorVersion; }

		void setMinorVersion(int i) { m_iMinorVersion = i; }
		int getMinorVersion() const { return m_iMinorVersion; }

	private:
		virtual void onKeyPress(int iKey) {}
		virtual void onKeyRelease(int iKey) {}
		virtual void onMouseMove(int iX, int iY) {}
		virtual void onMouseMoveRel(int iDX, int iDY) {}
		virtual void onMouseLeftClick(int iX, int iY) {}
		virtual void onMouseLeftRelease(int iX, int iY) {}
		virtual void onMouseRightClick(int iX, int iY) {}
		virtual void onMouseRightRelease(int iX, int iY) {}
		virtual void onWindowResize(int iWidth, int iHeight) {}

		bool m_bAppRunning;
		bool m_bInitialized;
		std::string m_sWindowTitle;
		int m_iWidth;
		int m_iHeight;
		bool m_bFullscreen;
		int m_iMajorVersion;
		int m_iMinorVersion;
		GLFWwindow* m_pWindow;

	};
}