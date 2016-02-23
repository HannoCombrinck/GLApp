#include "GLFWApp.h"

#include <Logging/Log.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/bind.hpp>

#include <assert.h>
#include <vector>

namespace baselib {

	GLFWApp::GLFWApp()
		: m_bAppRunning(false)
		, m_pWindow(NULL)
		, m_iMouseX(0)
		, m_iMouseY(0)
		, m_iMouseXPrev(0)
		, m_iMouseYPrev(0)
		, m_bLockMousePos(false)
		, m_dCurrentTime(0.0)
		, m_dPreviousTime(0.0)
		, m_iWidth(800)
		, m_iHeight(600)
		, m_bFullscreen(false)
		, m_iMajorVersion(3)
		, m_iMinorVersion(2)
		, m_sWindowTitle("GLFW Window")
	{
		LOG_VERBOSE << "GLFWApp constructor";
	}

	GLFWApp::~GLFWApp()
	{
		LOG_VERBOSE << "GLFWApp destructor";
		destroy();
	}

	namespace
	{
		void errorCallback(int iErrorCode, const char* szErrorMessage)
		{
			LOG_ERROR << "GLFW Error: " << iErrorCode << " : " << szErrorMessage;
		}

		// Event callback signals
		boost::signals2::signal<void (int iKey, int iActions)> KeyEventSignal;
		boost::signals2::signal<void (int iButton, int iAction)> MouseButtonSignal;
		boost::signals2::signal<void (int iEnter)> MouseEnterSignal;
		boost::signals2::signal<void (double dScroll)> MouseScrollSignal;
		boost::signals2::signal<void (int iWidth, int iHeight)> WindowMoveSignal;
		boost::signals2::signal<void (int iWidth, int iHeight)> WindowResizeSignal;
		boost::signals2::signal<void (int iWidth, int iHeight)> WindowFrameBufferResizeSignal;
		boost::signals2::signal<void ()> WindowRefreshSignal;
		boost::signals2::signal<void ()> WindowCloseSignal;
		boost::signals2::signal<void (const std::vector<std::string>& aPaths)> FileDropSignal;

		void keyEventCallback(GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods)
		{
			KeyEventSignal(iKey, iAction);

			if (iKey == GLFW_KEY_ESCAPE && iAction == GLFW_PRESS)
				glfwSetWindowShouldClose(pWindow, GL_TRUE);
		}

		void mouseButtonCallback(GLFWwindow* pWindow, int iButton, int iAction, int iMods)
		{
			MouseButtonSignal(iButton, iAction);
		}

		void mouseEnterCallback(GLFWwindow* pWindow, int iEnter)
		{
			MouseEnterSignal(iEnter);
		}

		void mouseScrollCallback(GLFWwindow* pWindow, double dX, double dY)
		{
			MouseScrollSignal(dY);
		}

		void windowMoveCallback(GLFWwindow* pWindow, int iWidth, int iHeight)
		{
			WindowMoveSignal(iWidth, iHeight);
		}

		void windowResizeCallback(GLFWwindow* pWindow, int iWidth, int iHeight)
		{
			WindowResizeSignal(iWidth, iHeight);
		}

		void windowFrameBufferResizeCallback(GLFWwindow* pWindow, int iWidth, int iHeight)
		{
			WindowFrameBufferResizeSignal(iWidth, iHeight);
		}

		void windowRefreshCallback(GLFWwindow* pWindow)
		{
			WindowRefreshSignal();
		}

		void windowCloseCallback(GLFWwindow* pWindow)
		{
			WindowCloseSignal();
		}

		void fileDropCallback(GLFWwindow* pWindow, int iNumFiles, const char** aPaths)
		{
			std::vector<std::string> asPaths;
			for (int i = 0; i < iNumFiles; ++i)
				asPaths.push_back(aPaths[i]);

			FileDropSignal(asPaths);
		}
	}

	void GLFWApp::init()
	{
		// Set error callback
		glfwSetErrorCallback(errorCallback);

		// Init GLFW
		if (!glfwInit())
		{
			LOG_ERROR << "GLFW init error";
			assert(false);
		}

		// Create window and set context
		GLFWmonitor *pMonitor = NULL;
		if (m_bFullscreen)
			pMonitor = glfwGetPrimaryMonitor();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_iMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_iMinorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // TODO: Test forward compatible vs not forward compatible
		m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, m_sWindowTitle.c_str(), pMonitor, NULL);
		if (!m_pWindow)
		{
			glfwTerminate();
			LOG_ERROR << "Failed to create GLFW window";
			assert(false);
		}
		glfwMakeContextCurrent(m_pWindow);

		// Initialize GL extension wrangler
		glewExperimental = true;
		auto eError = glewInit();
		if (eError != GLEW_OK)
		{
			LOG_ERROR << "Failed to initialize GLEW: " << glewGetErrorString(eError);
			assert(false);
		}

		// Setup event callbacks
		glfwSetKeyCallback(m_pWindow, keyEventCallback);
		m_KeyEventConnection = KeyEventSignal.connect(boost::bind(&GLFWApp::keyEvent, this, _1, _2));
		glfwSetMouseButtonCallback(m_pWindow, mouseButtonCallback);
		m_MouseButtonConnection = MouseButtonSignal.connect(boost::bind(&GLFWApp::mouseButton, this, _1, _2));
		glfwSetCursorEnterCallback(m_pWindow, mouseEnterCallback);
		m_MouseEnterConnection = MouseEnterSignal.connect(boost::bind(&GLFWApp::mouseEnter, this, _1));
		glfwSetScrollCallback(m_pWindow, mouseScrollCallback);
		m_MouseScrollConnection = MouseScrollSignal.connect(boost::bind(&GLFWApp::mouseScroll, this, _1));
		glfwSetWindowPosCallback(m_pWindow, windowMoveCallback);
		m_WindowMoveConnection = WindowMoveSignal.connect(boost::bind(&GLFWApp::windowMove, this, _1, _2));
		glfwSetWindowSizeCallback(m_pWindow, windowResizeCallback);
		m_WindowResizeConnection = WindowResizeSignal.connect(boost::bind(&GLFWApp::windowResize, this, _1, _2));
		glfwSetFramebufferSizeCallback(m_pWindow, windowFrameBufferResizeCallback);
		m_WindowFrameBufferResizeConnection = WindowFrameBufferResizeSignal.connect(boost::bind(&GLFWApp::windowFrameBufferResize, this, _1, _2));
		glfwSetWindowRefreshCallback(m_pWindow, windowRefreshCallback);
		m_WindowRefreshConnection = WindowRefreshSignal.connect(boost::bind(&GLFWApp::windowRefresh, this));
		glfwSetWindowCloseCallback(m_pWindow, windowCloseCallback);
		m_WindowCloseConnection = WindowCloseSignal.connect(boost::bind(&GLFWApp::windowClose, this));
		glfwSetDropCallback(m_pWindow, fileDropCallback);
		m_FileDropConnection = FileDropSignal.connect(boost::bind(&GLFWApp::fileDrop, this, _1));

		// Successfully created window and context
		setAppRunning(true);
		onInit(m_iWidth, m_iHeight);
	}

	void GLFWApp::destroy()
	{
		if (m_pWindow)
			glfwDestroyWindow(m_pWindow);
		glfwTerminate();
	}

	void GLFWApp::start()
	{
		LOG_VERBOSE << "Creating window with OpenGL context";
		init();

		LOG_VERBOSE << "GLFWApp starting main loop";

		m_dCurrentTime = GetTime();
		while (isAppRunning())
		{
			m_dPreviousTime = m_dCurrentTime;
			m_dCurrentTime = GetTime();

			processEvents();
			onUpdate(m_dCurrentTime - m_dPreviousTime);
			onRender();
			swapBuffers();
		}

		LOG_VERBOSE << "GLFWApp main loop stopped";
		onDestroy();
	}

	void GLFWApp::processEvents()
	{
		// Check if app should be closed e.g. close button was clicked
		if (glfwWindowShouldClose(m_pWindow))
			setAppRunning(false);

		glfwPollEvents();

		// Get mouse position manually and handle mouse movements
		mouseMove();
	}

	void GLFWApp::keyEvent(int iKey, int iAction)
	{
		if (iAction == GLFW_PRESS || iAction == GLFW_REPEAT)
			onKeyPress(iKey);
		else if (iAction == GLFW_RELEASE)
			onKeyRelease(iKey);
	}

	void GLFWApp::mouseButton(int iButton, int iAction)
	{
		switch (iButton)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			if (iAction == GLFW_PRESS)
				onMouseLeftClick(m_iMouseX, m_iMouseY);
			else if (iAction == GLFW_RELEASE)
				onMouseLeftRelease(m_iMouseX, m_iMouseY);
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			if (iAction == GLFW_PRESS)
				onMouseRightClick(m_iMouseX, m_iMouseY);
			else if (iAction == GLFW_RELEASE)
				onMouseRightRelease(m_iMouseX, m_iMouseY);
			break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			if (iAction == GLFW_PRESS)
				onMouseMiddleClick(m_iMouseX, m_iMouseY);
			else if (iAction == GLFW_RELEASE)
				onMouseMiddleRelease(m_iMouseX, m_iMouseY);
			break;

		default: assert(false); break;
		}
	}

	void GLFWApp::mouseScroll(double dScroll)
	{
		onMouseScroll(dScroll);
	}

	void GLFWApp::mouseEnter(int iEnter)
	{
		if (iEnter == GL_TRUE)
			onMouseEnter();
		else if (iEnter == GL_FALSE)
			onMouseExit();
	}

	void GLFWApp::mouseMove()
	{
		// Get mouse position
		double xPos = 0.0;
		double yPos = 0.0;
		glfwGetCursorPos(m_pWindow, &xPos, &yPos);
		m_iMouseXPrev = m_iMouseX;
		m_iMouseYPrev = m_iMouseY;
		m_iMouseX = int(floor(xPos));
		m_iMouseY = int(floor(yPos));

		// Handle mouse move
		if (m_iMouseX != m_iMouseXPrev || m_iMouseY != m_iMouseYPrev)
		{
			onMouseMove(m_iMouseX, m_iMouseY);
			onMouseMoveRel(m_iMouseX - m_iMouseXPrev, m_iMouseY - m_iMouseYPrev);
		}

		if (m_bLockMousePos)
		{
			m_iMouseX = m_iWidth/2;
			m_iMouseY = m_iHeight/2;
			glfwSetCursorPos(m_pWindow, m_iMouseX, m_iMouseY);
		}
	}

	void GLFWApp::windowMove(int iX, int iY)
	{
		onWindowMove(iX, iY);
	}

	void GLFWApp::windowResize(int iWidth, int iHeight)
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;
		onWindowResize(iWidth, iHeight);
	}

	void GLFWApp::windowFrameBufferResize(int iWidth, int iHeight)
	{
		onWindowFrameBufferResize(iWidth, iHeight);
	}

	void GLFWApp::windowRefresh()
	{
		onWindowRefresh();
	}

	void GLFWApp::windowClose()
	{
		onWindowClose();
	}

	void GLFWApp::fileDrop(const std::vector<std::string>& asPaths)
	{
		onFileDrop(asPaths);
	}

	void GLFWApp::swapBuffers()
	{
		glfwSwapBuffers(m_pWindow);
	}

	double GLFWApp::GetTime() const
	{
		return glfwGetTime();
	}

	void GLFWApp::setLockMousePosition(bool b)
	{
		m_bLockMousePos = b;
		m_iMouseX = m_iWidth/2;
		m_iMouseY = m_iHeight/2;
		glfwSetCursorPos(m_pWindow, m_iMouseX, m_iMouseY);

		int iCursorFlag = GLFW_CURSOR_NORMAL;
		if (m_bLockMousePos)
			iCursorFlag = GLFW_CURSOR_HIDDEN;

		glfwSetInputMode(m_pWindow, GLFW_CURSOR, iCursorFlag);
	}

	void GLFWApp::setWindowTitle(const std::string& s)
	{
		m_sWindowTitle = s;
		glfwSetWindowTitle(m_pWindow, s.c_str());
	}

	void GLFWApp::setSize(int iWidth, int iHeight)
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;
		glfwSetWindowSize(m_pWindow, m_iWidth, m_iHeight);
	}

	void GLFWApp::setFullScreen(bool b)
	{
		m_bFullscreen = b;
		// TODO: Toggle fullscreen mode
	}

}