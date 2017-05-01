#include "main2.h"

int main(void)
{
	return Main::Instance().run();
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
	Main::Instance().m_Displaysize = glm::ivec2(width, height);
	Main::Instance().SetupFramebuffer();
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// Invert Y-Coordinate
	Main::Instance().m_Cursor = glm::ivec2(xpos, Main::Instance().m_Displaysize.y - ypos);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
		std::cout << "Clicked On : " << Main::Instance().TrackedID() << std::endl;
}
glm::vec4 IntegerToColor(int i)
{
	int r = (i & 0x000000FF) >> 0;
	int g = (i & 0x0000FF00) >> 8;
	int b = (i & 0x00FF0000) >> 16;
	int a = (i & 0xFF000000) >> 24;
	return glm::vec4((r / 255.0f), (g / 255.0f), (b / 255.0f), (a / 255.0f));
}
int Main::run()
{
	/* Loop Until The User Closes The Window */
	while (!glfwWindowShouldClose(m_window))
	{
		/* Render here */
		render();

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	return 0;
}
void Main::render()
{
	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 Prepare FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer.ID);

	// Clear Scene Buffer
	glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear Picking Buffer (Should Be totally Black)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDrawBuffer(GL_COLOR_ATTACHMENT1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// MRT: Render Into Both Layers
	unsigned int drawbuffers[] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, drawbuffers);	

	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 Render Scene
	static float angle(0);
	angle += 0.001f;

	glEnable(GL_DEPTH_TEST);
	glUseProgram(m_program);

	// View
	glUniformMatrix4fv(
		glGetUniformLocation(m_program, "View"),
		1,
		false,
		glm::value_ptr(glm::lookAt(m_Camera, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))));

	// Projection
	glUniformMatrix4fv(
		glGetUniformLocation(m_program, "Projection"),
		1,
		false,
		glm::value_ptr(glm::perspective(3.14f / 4, (float)m_Displaysize.x / m_Displaysize.y, 0.1f, 100.0f)));

	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 First Triangle
	glUniformMatrix4fv(
		glGetUniformLocation(m_program, "Model"),
		1,
		false,
		glm::value_ptr(glm::translate(glm::vec3(-1, 0, 0)) * glm::rotate(angle, glm::vec3(0, 1, 0))));

	glUniform4fv(
		glGetUniformLocation(m_program, "IDcolor"),
		1,
		&IntegerToColor(100)[0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 Second Triangle
	glUniformMatrix4fv(
		glGetUniformLocation(m_program, "Model"),
		1,
		false,
		glm::value_ptr(glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(angle, glm::vec3(0, 1, 0))));

	glUniform4fv(
		glGetUniformLocation(m_program, "IDcolor"),
		1,
		&IntegerToColor(200)[0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 Third Triangle
	glUniformMatrix4fv(
		glGetUniformLocation(m_program, "Model"),
		1,
		false,
		glm::value_ptr(glm::translate(glm::vec3(1, 0, 0)) * glm::rotate(angle, glm::vec3(0, 1, 0))));

	glUniform4fv(
		glGetUniformLocation(m_program, "IDcolor"),
		1,
		&IntegerToColor(300)[0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);

	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 Picking
	unsigned char pixeldata[4];

	// reading pixel data at current cursor position ...
	glReadBuffer(GL_COLOR_ATTACHMENT1);	// read from second framebuffer layer
	glReadPixels(m_Cursor.x, m_Cursor.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixeldata);

	// convert pixel color back to (int)ID ...
	m_trackedID = (pixeldata[0] << 0) | (pixeldata[1] << 8) | (pixeldata[2] << 16) | (pixeldata[3] << 24);
	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
	// copy to system-framebuffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer.ID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glReadBuffer(GL_COLOR_ATTACHMENT0);	// default scene
	//glReadBuffer(GL_COLOR_ATTACHMENT1);	// that would show you the IDcolors

	glClearColor(1, 1, 1, 1);		// everything that is white is out of our framebuffers area
	glClear(GL_COLOR_BUFFER_BIT);

	glBlitFramebuffer(
		0, 0, m_Framebuffer.size.x, m_Framebuffer.size.y,
		0, 0, m_Framebuffer.size.x, m_Framebuffer.size.y,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);
	// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
}
unsigned int Main::TrackedID() const
{
	// ID at cursor position
	return m_trackedID;
}

Main::Main()
{
	/* Initialize the library */
	if (!glfwInit())
		exit(-1);

	/* Create a windowed mode window and its OpenGL context */
	m_Displaysize = glm::ivec2(640, 480);
	m_window = glfwCreateWindow(m_Displaysize.x, m_Displaysize.y, "Simple RayCasting Test v1.0", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(-1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);

	// set callback functions
	glfwSetWindowSizeCallback(m_window, window_size_callback);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetScrollCallback(m_window, scroll_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);

	/* Init GLEW* */
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(-2);
	}

	// create framebuffer
	glGenRenderbuffers(1, &m_Framebuffer.color0);	// default, for scene
	glGenRenderbuffers(1, &m_Framebuffer.color1);	// for picking
	glGenRenderbuffers(1, &m_Framebuffer.depth);	// depth buffer
	glGenFramebuffers(1, &m_Framebuffer.ID);

	SetupFramebuffer();
	SetupShader();
	SetupVertexArray();
}
Main& Main::Instance()
{
	static Main instance;
	return instance;
}
Main::~Main()
{
	glfwTerminate();
}

void Main::SetupFramebuffer()
{
	m_Framebuffer.size = m_Displaysize;

	// Resize ViewPort
	glViewport(0, 0, m_Framebuffer.size.x, m_Framebuffer.size.y);

	// Allocate Memory
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.color0);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, m_Framebuffer.size.x, m_Framebuffer.size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.color1);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, m_Framebuffer.size.x, m_Framebuffer.size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Framebuffer.depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_Framebuffer.size.x, m_Framebuffer.size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Attach To FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer.ID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_Framebuffer.color0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, m_Framebuffer.color1);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Framebuffer.depth);

	// Show Errors
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
void Main::SetupShader()
{
	// shaders
	std::string vertexshader =
		"#version 400\n"\
		"layout(location = 0) in vec3 VertexPosition;\n"\
		"layout(location = 1) in vec4 VertexColor;\n"\
		"out vec4 color;\n"\
		"uniform mat4 Model, View, Projection;\n"\
		"void main()\n"\
		"{\n"\
		"	mat4 MVP = Projection * View * Model;\n"\
		"	gl_Position = MVP * vec4(VertexPosition, 1);\n"\
		"	color = VertexColor;\n"\
		"}\n"\
		;

	std::string fragmentshader =
		"#version 400\n"\
		"in vec2 TextureCoords;\n"\
		"in vec4 color;\n"\
		"layout (location = 0) out vec4 FragmentColor0;"\
		"layout(location = 1) out vec4 FragmentColor1;"\
		"uniform vec4 IDcolor;"\
		"void main()\n"\
		"{\n"\
		"	FragmentColor0 = color;\n"\
		"	FragmentColor1 = IDcolor;\n"\
		"}\n"\
		;


	// reset error log
	GLenum ErrorCheckValue = glGetError();

	// create shaders
	GLuint shadervertexID = glCreateShader(GL_VERTEX_SHADER);
	GLuint shaderfragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	// openGL wants for every shader an array of c-strings as source code
	const char* sourcecodearrayVS[] = { vertexshader.c_str() };
	const char* sourcecodearrayFS[] = { fragmentshader.c_str() };

	// set source code for shaders
	glShaderSource(shadervertexID, 1, sourcecodearrayVS, nullptr);
	glShaderSource(shaderfragmentID, 1, sourcecodearrayFS, nullptr);

	// compile shaders
	glCompileShader(shadervertexID);
	glCompileShader(shaderfragmentID);

	// create program
	m_program = glCreateProgram();

	// attach shaders to program
	glAttachShader(m_program, shadervertexID);
	glAttachShader(m_program, shaderfragmentID);

	// link program
	glLinkProgram(m_program);

	// tag for deletion (takes effect when no shader program uses them anymore)
	glDeleteShader(shadervertexID);
	glDeleteShader(shaderfragmentID);

	// check for errors ...
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cout << "ERROR: cannot load shaders:   errorcode = " << ErrorCheckValue << std::endl;
		system("PAUSE");
		exit(-1);
	}
}
void Main::SetupVertexArray()
{
	float vertices[] = {
		//   xyz                        rgba
		0.0f, 0.0f, 0.0f,		 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,		 0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,		 0.0f, 0.0f, 1.0f, 1.0f,
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 0));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
