#pragma once
#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>

namespace loft { namespace graphics {

#define MAX_KEYS		1024;
#define MAX_BUTTONS		32;
	//above not working for bool arrays below
  
	class Window
	{
	friend struct GLFWwindow;

	private:
		const char *m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;

		bool m_Keys[1024];
		bool m_KeyState[1024];
		bool m_KeyTyped[1024];
		bool m_MouseButtons[32];
		bool m_MouseState[32];
		bool m_MouseClicked[32];
		double mx, my;
	
	public:
		Window(const char *name, int width, int height);
		~Window();
		bool closed() const;
		void update();
		void clear() const;

		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		bool isKeyPressed(unsigned int keycode) const;
		bool isKeyTyped(unsigned int keycode) const;
		bool isMouseButtonPressed(unsigned int button) const;
		bool isMouseButtonClicked(unsigned int button) const;
		void getMousePosition(double& x, double& y) const;

	private:
		bool init();
		friend void  window_resize(GLFWwindow* window, int width, int height);
		friend void  key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void  mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void  cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	};

} }