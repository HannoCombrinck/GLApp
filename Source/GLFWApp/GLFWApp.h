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

		void SetWindowTitle(const std::string& s) { m_sWindowTitle = s; }
		std::string GetWindowTitle() const { return m_sWindowTitle; }

		void SetWidth(int i) { m_iWidth = i; }
		int GetWidth() const { return m_iWidth; }

		void SetHeight(int i) { m_iHeight = i; }
		int GetHeight() const { return m_iHeight; }

		void SetFullScreen(bool b) { m_bFullscreen = b; }
		bool GetFullScreen() const { return m_bFullscreen; }

		void SetMajorVersion(int i) { m_iMajorVersion = i; }
		int GetMajorVersion() const { return m_iMajorVersion; }

		void SetMinorVersion(int i) { m_iMinorVersion = i; }
		int GetMinorVersion() const { return m_iMinorVersion; }

	private:
		std::string m_sWindowTitle;
		int m_iWidth;
		int m_iHeight;
		bool m_bFullscreen;
		int m_iMajorVersion;
		int m_iMinorVersion;
		GLFWwindow* m_pWindow;

	};
}