#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64/glfw3.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <string>

namespace QuadCore
{
	class Display
	{
	public:
		Display();
		Display(int width, int height, const std::string& title);
		virtual ~Display();

	private:
		Display(const Display& other) {}
		void operator=(const Display& other) {}

	private:
		GLFWwindow *window;
		int m_width;
		int m_height;
		struct framebuffer
		{
			unsigned int ID;
			unsigned int color0, color1, depth;
		} m_Framebuffer;
		unsigned int m_trackedID;
		unsigned char pixeldata[4];
		int m_CursorX;
		int m_CursorY;

	public:
		void SetCursor(int x, int y)
		{
			m_CursorX = x;
			m_CursorY = y;
		}
		void Clear(float r, float g, float b, float a);
		void Update();
		bool IsClosed();
		framebuffer GetFrameBuffer()
		{
			return m_Framebuffer;
		}

	public:
		void GetWindowSize(int* width, int* height)
		{
			*width = m_width;
			*height = m_height;
		}
		float GetWindowAspec()
		{
			return ((float)m_width / (float)m_height);
		}
		void UpdateWindowSize()
		{
			glfwGetFramebufferSize(window, &m_width, &m_height);
			glViewport(0, 0, m_width, m_height);
		}
		GLFWwindow* GetWindow()
		{
			return window;
		}
		void SetupFramebuffer();
		glm::vec4 IntegerToColor(int i);
		unsigned int GetTrackedID()
		{
			return m_trackedID;
		}
		void SetTrackedID(int n)
		{
			m_trackedID = n;
		}
		unsigned char* GetPixelData()
		{
			return pixeldata;
		}
	};
}
