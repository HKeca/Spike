#include "window.h"


namespace spike { namespace graphics {

	void window_resize(GLFWwindow *window, int width, int height);

	Window::Window(const char *title, int width, int height)
	{
		// Set window attributes
		m_Title = title;
		m_Width = width;
		m_Height = height;

		// Init opengl
		if (!init())
			glfwTerminate();

		// Init key/mouse inputs
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
		}
	}

	Window::~Window()
	{
		// Close opengl
		glfwTerminate();
	}

	/*
		Init window
	*/
	bool Window::init()
	{
		// Opengl init
		if (!glfwInit())
		{
			std::cout << "Failed to init glfw" << std::endl;
			return false;
		}

		// create window
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		// window creation failed
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create GLFW window" << std::endl;
			return false;
		}

		// set opengl context
		glfwMakeContextCurrent(m_Window);
		// Window pointer
		glfwSetWindowUserPointer(m_Window, this);
		// set window callbacks
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);

		// Glew init
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Couldn't init GLEW" << std::endl;
			return false;
		}

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		return true;
	}

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		//TODO: log error

		// if keycode is out of range of MAX_KEYS
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		//TODO: log error

		// if button code is out of range of MAX_BUTTONS
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		// set mouse position
		x = mx;
		y = my;
	}


	void Window::clear() const
	{
		// opengl clear the window
		return glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const
	{
		// close the window
		return glfwWindowShouldClose(m_Window);
	}

	void Window::update() const
	{
		// Check for errors
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;

		// update window events
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void window_resize(GLFWwindow *window, int width, int height)
	{
		// resize the viewport
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);

		// set bool according to key release or key press
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		// set bool according to button release or key press
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		
		// Set cursor position
		win->mx = xpos;
		win->my = ypos;
	}
} }