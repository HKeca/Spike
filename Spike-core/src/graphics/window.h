#pragma once

#include <glfw3.h>
#include <iostream>

namespace spike { namespace graphics {
		
	class Window
	{
	private:
		const char *m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;
	public:
		Window(const char *name, int width, int height);
		~Window();
		bool closed() const;
		void clear() const;
		void update() const;
	private:
		bool init();
	};

} }