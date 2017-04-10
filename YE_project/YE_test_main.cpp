#include <sb7.h>
#include "object.h"
#include "shader.h"
#include <sb7ktx.h>

class simpleclear_app : public sb7::application
{
public:
	void init()
	{
		static const char title[] = "OpenGL SuperBible - Simple Clear";

		sb7::application::init();

		memcpy(info.title, title, sizeof(title));
	}

	void startup();
	void render(double currentTime);

protected:
	sb7::object object;

};


void simpleclear_app::startup()
{
	object.load("../media/objects/sphere.sbm");

	//load_shaders();
}

void simpleclear_app::render(double currentTime)
{
	static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, red);

	object.render();
}


DECLARE_MAIN(simpleclear_app)
