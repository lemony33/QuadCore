#include "Display.h"



Display::Display(int width, int height, const std::string& title)
{
	/* Initialize the library */
	if (!glfwInit())
		return;
		//return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!window) {
		glfwTerminate();
		return;
		//return -1;
	}

	// callbacks here

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//// Initialize GLEW
	//glewExperimental = true;	// N

	// Initialize GLEW
	glewExperimental = true;	// Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
		//return -1;
	}

	printf("%s\n", glGetString(GL_VERSION));
	
	glfwGetFramebufferSize(window, &m_width, &m_height);

	//m_isClosed = false;
}

Display::~Display()
{
	glfwTerminate();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// <-depth test
}

bool Display::IsClosed()
{
	//return m_isClosed;
	return glfwWindowShouldClose(window);
}

void Display::Update()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
}