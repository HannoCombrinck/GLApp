#include "GLFWApp.h"

#include <Logging/Log.h>
#include <GLFW/glfw3.h>

#include <assert.h>
#include <vector>

using namespace std;

namespace baselib {

	GLFWApp::GLFWApp()
		: m_bAppRunning(false)
		, m_bInitialized(false)
		, m_sWindowTitle("GLFWApp")
		, m_iWidth(640)
		, m_iHeight(480)
		, m_bFullscreen(false)
		, m_iMajorVersion(3)
		, m_iMinorVersion(2)
		, m_pWindow(NULL)
		, m_iMouseX(0)
		, m_iMouseY(0)
		, m_iMouseXPrev(0)
		, m_iMouseYPrev(0)
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

		enum EventType
		{
			INVALID_EVENT,
			KEY_EVENT,
			MOUSE_BUTTON_EVENT,
			MOUSE_SCROLL_EVENT,
			MOUSE_ENTER_EVENT
		};

		struct InputEvent
		{
			InputEvent() : eType(INVALID_EVENT), i1(0), i2(0), i3(0), d1(0.0) {}

			EventType eType;
			int i1;
			int i2;
			int i3;
			double d1;
		};

		std::vector<InputEvent> aEvents;

		void keyEventCallback(GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods)
		{
			LOG_DEBUG << "Key : " << iKey << " , " << iScancode << " , " << iAction;

			InputEvent sEvent;
			sEvent.eType = KEY_EVENT;
			sEvent.i1 = iKey;
			sEvent.i2 = iScancode;
			sEvent.i3 = iAction;
			aEvents.push_back(sEvent);

			if (iKey == GLFW_KEY_ESCAPE && iAction == GLFW_PRESS)
				glfwSetWindowShouldClose(pWindow, GL_TRUE);
		}

		void mouseButtonCallback(GLFWwindow* pWindow, int iButton, int iAction, int iMods)
		{
			LOG_DEBUG << "Mouse button: " << iButton << " , " << iAction;

			InputEvent sEvent;
			sEvent.eType = MOUSE_BUTTON_EVENT;
			sEvent.i1 = iButton;
			sEvent.i2 = iAction;
			aEvents.push_back(sEvent);
		}

		void mouseEnterCallback(GLFWwindow* pWindow, int iEnter)
		{
			LOG_DEBUG << "Mouse enter: " << iEnter;

			InputEvent sEvent;
			sEvent.eType = MOUSE_ENTER_EVENT;
			sEvent.i1 = iEnter;
			aEvents.push_back(sEvent);
		}

		void mouseScrollCallback(GLFWwindow* pWindow, double dX, double dY)
		{
			LOG_DEBUG << "Mouse scroll : dx = " << dX << " , dy = " << dY;

			InputEvent sEvent;
			sEvent.eType = MOUSE_SCROLL_EVENT;
			sEvent.d1 = dY;
			aEvents.push_back(sEvent);
		}
	}

	void GLFWApp::init()
	{
		// Set error callback
		glfwSetErrorCallback(errorCallback);

		// Init GLFW
		if (!glfwInit())
			assert("GLFW init error" && false);

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
			assert("Failed to create GLFW window" && false);
		}
		glfwMakeContextCurrent(m_pWindow);

		// Set event callbacks
		glfwSetKeyCallback(m_pWindow, keyEventCallback);
		glfwSetMouseButtonCallback(m_pWindow, mouseButtonCallback);
		glfwSetCursorEnterCallback(m_pWindow, mouseEnterCallback);
		glfwSetScrollCallback(m_pWindow, mouseScrollCallback);

		// Successfully created window and context
		setAppRunning(true);
		setInitialized(true);

		onInit();
	}

	void GLFWApp::destroy()
	{
		if (!isInitialized())
			return;
		
		onDestroy();

		if (m_pWindow)
			glfwDestroyWindow(m_pWindow);
		glfwTerminate();

		setInitialized(false);
	}

	void GLFWApp::processEvents()
	{
		// Check if app should be closed e.g. close button was clicked
		if (glfwWindowShouldClose(m_pWindow))
			setAppRunning(false);

		// Let callbacks create event queue
		glfwPollEvents();

		// Get mouse position and handle mouse movements
		mouseMove();

		// Process event queue
		while (!aEvents.empty())
		{
			auto sEvent = aEvents.back();
			aEvents.pop_back();
			switch (sEvent.eType)
			{
				case KEY_EVENT: keyEvent(sEvent.i1 /*sEvent.i2*/, sEvent.i3); break;
				case MOUSE_BUTTON_EVENT: mouseButton(sEvent.i1, sEvent.i2); break;
				case MOUSE_ENTER_EVENT: mouseEnter(sEvent.i1); break;
				case MOUSE_SCROLL_EVENT: mouseScroll(sEvent.d1); break;
				default: assert(false); break;
			}
		}
	}

	void GLFWApp::keyEvent(int iKey, int iAction)
	{
		if (iAction == GLFW_PRESS || iAction == GLFW_REPEAT)
			onKeyPress(iKey);
		else if (iAction == GLFW_RELEASE)
			onKeyRelease(iKey);
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
			LOG_DEBUG << "New mouse pos : " << m_iMouseX << " , " << m_iMouseY;
			LOG_DEBUG << "Delta mouse : " << m_iMouseX - m_iMouseXPrev << " , " << m_iMouseY - m_iMouseYPrev;

			onMouseMove(m_iMouseX, m_iMouseY);
			onMouseMoveRel(m_iMouseX - m_iMouseXPrev, m_iMouseY - m_iMouseYPrev);
		}
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

	void GLFWApp::swapBuffers()
	{
		assert(isInitialized() && "App must be initialized before calling GLFWApp::swapBuffers()");
		glfwSwapBuffers(m_pWindow);
	}

	double GLFWApp::GetTime() const
	{
		return glfwGetTime();
	}

}