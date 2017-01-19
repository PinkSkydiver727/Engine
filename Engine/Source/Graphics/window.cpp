#include "window.h"

namespace loft { namespace graphics {
	


	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init())
		{
			glfwTerminate();
		}

		for (int i = 0; i < 1024; i++)
		{
			m_Keys[i] = false;
			m_KeyState[i] = false;
			m_KeyTyped[i] = false;
		}
		for (int i = 0; i < 32; i++)
		{
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}

	}
	Window::~Window()
	{
		glfwTerminate();
	}
	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Error" << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create glfw window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window); 
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);

		glfwSwapInterval(0.0);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Could not init GLEW" << std::endl;
			return false;
		}


		return true;
	}


	bool Window::isKeyPressed(unsigned int keycode) const
	{
		if (keycode >= 1024)
		{
			return false;
		}
		return m_Keys[keycode];
	}

	bool Window::isKeyTyped(unsigned int keycode) const
	{
		if (keycode >= 1024)
		{
			return false;
		}
		return m_KeyTyped[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		if (button >= 32)
		{
			return false;
		}
		return m_MouseButtons[button];
	}

	bool Window::isMouseButtonClicked(unsigned int button) const
	{
		if (button >= 32)
		{
			return false;
		}
		return m_MouseClicked[button];
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		x = mx;
		y = my;
	}


	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}


	void Window::update() 
	{
		for (int i = 0; i < 1024; i++)
		{
			//Set pressed keys
			if (m_Keys[i])
			{
				m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];
			}
		}
		memcpy(m_KeyState, m_Keys, 1024);

		//set clicked mouse buttons 
		for (int i = 0; i < 32; i++)
		{
			//
			if (m_MouseButtons[i])
			{
				m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];
			}
		}

		
		memcpy(m_MouseState, m_MouseButtons, 32);
		

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << error << std::endl;
		}

		glfwPollEvents();
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);

	}

	void window_resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
	}

	void  key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		
		win->m_Keys[key] = action != GLFW_RELEASE;
	}
	void  mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void  cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}


} }