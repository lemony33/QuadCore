#include "Display.h"

using QuadCore::Display;

Display::Display(int width, int height, const std::string& title)
{
	if (!glfwInit())
		return;

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	window2 = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;	// Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	printf("%s\n", glGetString(GL_VERSION));
	
	glEnable(GL_DEPTH_TEST);	// 가려진 면 제거
	glEnable(GL_CULL_FACE);		// 후면 제거
	glCullFace(GL_BACK);
}

Display::~Display()
{
	glfwTerminate();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// <-depth test
}

bool Display::IsClosed()
{
	return glfwWindowShouldClose(window);
}

void Display::Update()
{
	std::string text;
	text = "This is a simple text";
	glColor3f(0, 1, 0);
	drawText(text.data(), text.size(), 50, 200);

	glfwSwapBuffers(window);
	glfwPollEvents();
}