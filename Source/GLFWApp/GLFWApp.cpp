#include "GLFWApp.h"

#include <assert.h>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

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

	}

	GLFWApp::~GLFWApp()
	{
		destroy();
	}

	namespace
	{
		void errorCallback(int iErrorCode, const char* szErrorMessage)
		{
			cout << "GLFW Error: " << iErrorCode << " : " << szErrorMessage << endl;
		}

		enum EventType
		{
			KEY_EVENT,
			MOUSE_BUTTON_EVENT,
			MOUSE_SCROLL_EVENT,
			MOUSE_ENTER_EVENT
		};

		struct GLFWEvent
		{
			GLFWEvent(EventType _eType, int _i1, int _i2, int _i3) 
				: eType(_eType)
				, i1(_i1)
				, i2(_i2)
				, i3(_i3)
			{ }

			EventType eType;
			int i1;
			int i2;
			int i3;
		};

		std::vector<GLFWEvent> aEvents;

		void keyEventCallback(GLFWwindow* pWindow, int iKey, int iScancode, int iAction, int iMods)
		{
			cout << "Key : " << iKey << " , " << iScancode << " , " << iAction << endl;
			aEvents.push_back(GLFWEvent(KEY_EVENT, iKey, iScancode, iAction));
			if (iKey == GLFW_KEY_ESCAPE && iAction == GLFW_PRESS)
				glfwSetWindowShouldClose(pWindow, GL_TRUE);
		}

		void mouseButtonCallback(GLFWwindow* pWindow, int iButton, int iAction, int iMods)
		{
			cout << "Mouse button: " << iButton << " , " << iAction << endl;
			aEvents.push_back(GLFWEvent(MOUSE_BUTTON_EVENT, iButton, iAction, 0));
		}

		void mouseEnterCallback(GLFWwindow* pWindow, int iEnter)
		{
			cout << "Mouse enter: " << iEnter << endl;
			aEvents.push_back(GLFWEvent(MOUSE_ENTER_EVENT, iEnter, 0, 0));
		}

		void mouseScrollCallback(GLFWwindow* pWindow, double dX, double dY)
		{
			cout << "Mouse scroll : dx = " << dX << " , dy = " << dY << endl;
			aEvents.push_back(GLFWEvent(MOUSE_SCROLL_EVENT, int(dY), 0, 0));
		}
	}

	void GLFWApp::start()
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
		m_bInitialized = true;
	}

	void GLFWApp::destroy()
	{
		if (!m_bInitialized)
			return;
		 
		if (m_pWindow)
			glfwDestroyWindow(m_pWindow);
		glfwTerminate();

		m_bInitialized = false;
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
				case MOUSE_SCROLL_EVENT: mouseScroll(sEvent.i1); break;
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
			cout << "New mouse pos : " << m_iMouseX << " , " << m_iMouseY << endl;
			cout << "Delta mouse : " << m_iMouseX - m_iMouseXPrev << " , " << m_iMouseY - m_iMouseYPrev << endl;

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

	void GLFWApp::mouseScroll(int iScroll)
	{
		onMouseScroll(iScroll);
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
		assert(m_bInitialized && "App must be initialized before calling GLFWApp::swapBuffers()");
		glfwSwapBuffers(m_pWindow);
	}

}