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

		struct FrameBuffer
		{
			glm::ivec2 size;
			unsigned int ID;
			unsigned int color_default;
			unsigned int color_picking;
			unsigned int depth;
		} m_Framebuffer;

		unsigned int m_trackedID;
		unsigned char pixeldata[4];
		int m_CursorX;
		int m_CursorY;
		bool isPrint;
		bool isMouseClicked;

	public:
		void SetPrint(bool b)
		{
			isPrint = b;
		}
		bool GetPrint()
		{
			return isprint;
		}
		void SetCursor(int x, int y)
		{
			m_CursorX = x;
			m_CursorY = y;
		}
		void Clear(float r, float g, float b, float a);
		void Update();
		bool IsClosed();

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
		int GetWindowWidth() { return m_width; }
		int GetWindowHeight() { return m_height; }
		void PrepareFrameBufferForRender(int color_r, int color_g, int color_b, int color_a);
		glm::vec4 IntegerToColor(int i);
		void SetIsMouseClicked(bool b)
		{
			isMouseClicked = b;
		}
		void MousePicking();
	};
}
