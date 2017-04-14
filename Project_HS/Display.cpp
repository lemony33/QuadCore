#include "Display.h"

Display::Display(int width, int height, const std::string& title)
{
	if (!glfwInit())
		return;

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

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

	glfwGetFramebufferSize(window, &m_width, &m_height);

	// 오브젝트 투과해서 보이는 현상 감소(1)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	setMouseEvent();
}

Display::~Display()
{
	glfwTerminate();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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