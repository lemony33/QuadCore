#pragma once
#include <sb7.h>

class HS_Graphics_Simulator : public sb7::application
{
public:
	HS_Graphics_Simulator() {};
	virtual ~HS_Graphics_Simulator() {};

private:
	GLuint rendering_program;
	GLuint vertex_array_object;
	GLuint program;

public:
	void init();
	void startup();
	GLuint compile_shaders(void);
	void render(double currentTime);
	void shutdown();
};