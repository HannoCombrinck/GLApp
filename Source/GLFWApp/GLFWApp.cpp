#include "GLFWApp.h"

#include <assert.h>
#include <iostream>

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

		static void keyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			cout << "Key: " << key << " , Action: " << action << endl;

			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
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
		if (glfwWindowShouldClose(m_pWindow))
			setAppRunning(false);

		glfwPollEvents();
		// TODO: Handle additional events manually e.g. mouse move.
	}

	void GLFWApp::swapBuffers()
	{
		assert(m_bInitialized && "App must be initialized before calling GLFWApp::swapBuffers()");
		glfwSwapBuffers(m_pWindow);
	}

}