#include "window.h"


namespace spike { namespace graphics {

	void windowResize(GLFWwindow *window, int width, int height);

	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;

		if (!init())
			glfwTerminate();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	/*
		
	*/
	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to init glfw" << std::endl;
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create GLFW window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, windowResize);

		return true;
	}

	void Window::clear() const
	{
		return glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void windowResize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
} }