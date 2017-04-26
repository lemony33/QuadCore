#include "Display.h"

using QuadCore::Display;

Display::Display()
{
	glGenRenderbuffers(1, &m_Framebuffer.color0);	// default, for scene
	glGenRenderbuffers(1, &m_Framebuffer.color1);	// for picking
	glGenRenderbuffers(1, &m_Framebuffer.depth);	// depth buffer
	glGenFramebuffers(1, &m_Framebuffer.ID);

	SetupFramebuffer();
	//SetupShader();
	//SetupVertexArray();
}
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
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer.ID);

	// Default Scene (Display Part)
	glClearColor(r, g, b, a);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Picking Pixel Scene (Display Part)
	glClearColor(0, 0, 0, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render Into Both Layers (Display Part)
	unsigned int drawbuffers[] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, drawbuffers);

	// Read Pixels (Mouse Picking Part)
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glReadPixels(m_CursorX, m_CursorY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixeldata);

	// Convert Pixel Color Back To ID (Mouse Picking Part)
	m_trackedID = ((pixeldata[0] << 0) | (pixeldata[1] << 8) | (pixeldata[2] << 16) | (pixeldata[3] << 24));

	// Copy to System-FrameBuffer (Mouse Picking Part)
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_trackedID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glReadBuffer(GL_COLOR_ATTACHMENT1);
	//glReadBuffer(GL_COLOR_ATTACHMENT1);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBlitFramebuffer(
		0, 0, m_width, m_height,
		0, 0, m_width, m_height,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);
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
	// Allocate Memory
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.color0);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, m_width, m_height);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.color1);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, m_width, m_height);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_width, m_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Attach To FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer.ID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_Framebuffer.color0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, m_Framebuffer.color1);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Framebuffer.depth);
}

glm::vec4 Display::IntegerToColor(int i)
{
	int r = (i & 0x000000FF) >> 0;
	int g = (i & 0x0000FF00) >> 8;
	int b = (i & 0x00FF0000) >> 16;
	int a = (i & 0xFF000000) >> 24;
	return glm::vec4((r / 255.0f), (g / 255.0f), (b / 255.0f), (a / 255.0f));
}