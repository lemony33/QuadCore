#include "Display.h"
#include <iostream>

using QuadCore::Display;

Display::Display() {}
Display::Display(int width, int height, const std::string& title)
{
	if (!glfwInit()) { return; }
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// SET-FRAMEBUFFER
	SetupFramebuffer();
	//

	printf("%s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}
Display::~Display()
{
	glfwTerminate();
}
void Display::Clear(float r, float g, float b, float a)
{
	PrepareFrameBufferForRender(r, g, b, a);

	// Render Here
	// Shader
	// Mesh


}
bool Display::IsClosed()
{
	return glfwWindowShouldClose(window);
}
void Display::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Display::SetupFramebuffer()
{
	// #1  Create FrameBuffers
	glGenRenderbuffers(1, &m_Framebuffer.color_default);
	glGenRenderbuffers(1, &m_Framebuffer.color_picking);
	glGenRenderbuffers(1, &m_Framebuffer.depth);
	glGenFramebuffers(1, &m_Framebuffer.ID);

	m_Framebuffer.size = glm::ivec2(m_width, m_height);
	glViewport(0, 0, m_Framebuffer.size.x, m_Framebuffer.size.y);

	// #2  Allocate Memory
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.color_default);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, m_Framebuffer.size.x, m_Framebuffer.size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.color_picking);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, m_Framebuffer.size.x, m_Framebuffer.size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_Framebuffer.size.x, m_Framebuffer.size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// #3  Attach To FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer.ID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_Framebuffer.color_default);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, m_Framebuffer.color_picking);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Framebuffer.depth);

	// #4  Error Check
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR: Framebuffer incomplete: ";
		if (status == GL_FRAMEBUFFER_UNDEFINED)
			std::cout << "undefined framebuffer";
		if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
			std::cout << "a necessary attachment is uninitialized";
		if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
			std::cout << "no attachments";
		if (status == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
			std::cout << "incomplete draw buffer";
		if (status == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
			std::cout << "incomplete read buffer";
		if (status == GL_FRAMEBUFFER_UNSUPPORTED)
			std::cout << "combination of attachments is not supported";
		if (status == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
			std::cout << "number if samples for all attachments does not match";
		std::cout << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Display::PrepareFrameBufferForRender(int color_r, int color_g, int color_b, int color_a)
{
	glGenFramebuffers(1, &m_Framebuffer.ID);

	// Clear Default Scene
	glClearColor(color_r, color_g, color_b, color_a);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear Picking
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDrawBuffer(GL_COLOR_ATTACHMENT1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render Into Both Layers
	unsigned int drawbuffers[] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, drawbuffers);
}
glm::vec4 Display::IntegerToColor(int i)
{
	int r = (i & 0x000000FF) >> 0;
	int g = (i & 0x0000FF00) >> 8;
	int b = (i & 0x00FF0000) >> 16;
	int a = (i & 0xFF000000) >> 24;
	return glm::vec4((r / 255.0f), (g / 255.0f), (b / 255.0f), (a / 255.0f));
}
void Display::MousePicking()
{
	// Mouse Picking
	if (isMouseClicked == true)
	{
		// Read Pixel-Data at Current Cursor Point
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glReadPixels(m_CursorX, m_CursorY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixeldata);

		// Save Pixel-Data
		m_trackedID = ((pixeldata[0] << 0) | (pixeldata[1] << 8) | (pixeldata[2] << 16) | (pixeldata[3] << 24));
		std::cout << "Pixel Data : " << m_trackedID << std::endl;
		//std::cout << "Pixel Data : [ " << pixeldata[0] << ", " << pixeldata[1] << ", "<< pixeldata[2] << ", " << pixeldata[3] << " ]" << std::endl;
		isMouseClicked = false;
	}

	// Copy to System-FrameBuffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_trackedID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glReadBuffer(GL_COLOR_ATTACHMENT0);	// Defualt Scene

	//glClearColor(1, 1, 1, 1);
	//glClear(GL_COLOR_BUFFER_BIT);

	glBlitFramebuffer(
		0, 0, m_Framebuffer.size.x, m_Framebuffer.size.y,
		0, 0, m_Framebuffer.size.x, m_Framebuffer.size.y,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);
}