/*
* Copyright ?2012-2015 Graham Sellers
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice (including the next
* paragraph) shall be included in all copies or substantial portions of the
* Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#include <sb7.h>
#include <vmath.h>

#include <object.h>
#include <sb7ktx.h>
#include <shader.h>

#define DEPTH_TEXTURE_SIZE      4096
#define FRUSTUM_DEPTH           1000
const int NUMBER = 128;

class ray_and_shadow : public sb7::application
{
public:
	ray_and_shadow()
		: prepare_program(0),
		trace_program(0),
		blit_program(0),
		max_depth(1),
		debug_depth(0),
		debug_mode(DEBUG_NONE),
		light_program(0), // shadow
		view_program(0), // shadow
		show_light_depth_program(0), // shadow
		mode(RENDER_FULL), // shadow
		paused(false)
	{
	}

protected:
	void init()
	{
		static const char title[] = "OpenGL SuperBible - Ray Tracing + Shadow Mapping";

		sb7::application::init();

		memcpy(info.title, title, sizeof(title));
	}

	void startup();
	void render(double currentTime);
	void onKey(int key, int action);

	void onMouseButton(int button, int action);

	void onMouseWheel(int pos);

	void onMouseMove(int x, int y);

	/*
	void init()
	{
	sb7::application::init();
	info.windowWidth = 0;
	info.windowHeight = 0;
	info.flags.fullscreen = 1;
	}
	*/
	void load_shaders();

	GLuint          prepare_program;
	GLuint          trace_program;
	GLuint          blit_program;

	GLuint          light_program; // shadow
	GLuint          view_program; // shadow
	GLint           show_light_depth_program; // shadow

	struct uniforms_block
	{
		vmath::mat4     mv_matrix;
		vmath::mat4     view_matrix;
		vmath::mat4     proj_matrix;
	};

	GLuint          uniforms_buffer;
	GLuint          sphere_buffer;
	GLuint          plane_buffer;
	GLuint          light_buffer;

	struct
	{
		GLint           ray_origin;
		GLint           ray_lookat;
		GLint           aspect;
	} uniforms;
	/////////////////////////////////////////////////////////////////////
	struct
	{
		struct
		{
			GLint   mvp;
		} light;
		struct
		{
			GLint   mv_matrix;
			GLint   proj_matrix;
			GLint   shadow_matrix;
			GLint   full_shading;
		} view;
	} smuniforms; 

	GLuint          depth_fbo;
	GLuint          depth_tex;
	GLuint          depth_debug_tex;

	enum { OBJECT_COUNT = 4 };
	struct
	{
		sb7::object     obj;
		vmath::mat4     model_matrix;
	} objects[OBJECT_COUNT];

	vmath::mat4     light_view_matrix;
	vmath::mat4     light_proj_matrix;

	vmath::mat4     camera_view_matrix;
	vmath::mat4     camera_proj_matrix;
	
	enum
	{
		RENDER_FULL,
		RENDER_LIGHT,
		RENDER_DEPTH
	} mode;
	////////////////////////////////////////////////////////////////// shadow

	GLuint          vao;

	struct sphere
	{
		vmath::vec3     center;
		float           radius;
		// unsigned int    : 32; // pad
		vmath::vec4     color;
	};

	struct plane
	{
		vmath::vec3     normal;
		float           d;
	};

	struct light
	{
		vmath::vec3     position;
		unsigned int : 32;       // pad
	};

	enum
	{
		MAX_RECURSION_DEPTH = 5,
		MAX_FB_WIDTH = 2048,
		MAX_FB_HEIGHT = 1024
	};

	enum DEBUG_MODE
	{
		DEBUG_NONE,
		DEBUG_REFLECTED,
		DEBUG_REFRACTED,
		DEBUG_REFLECTED_COLOR,
		DEBUG_REFRACTED_COLOR
	};

	GLuint              tex_composite;
	GLuint              ray_fbo[MAX_RECURSION_DEPTH];
	GLuint              tex_position[MAX_RECURSION_DEPTH];
	GLuint              tex_reflected[MAX_RECURSION_DEPTH];
	GLuint              tex_reflection_intensity[MAX_RECURSION_DEPTH];
	GLuint              tex_refracted[MAX_RECURSION_DEPTH];
	GLuint              tex_refraction_intensity[MAX_RECURSION_DEPTH];

	int                 max_depth;
	int                 debug_depth;
	DEBUG_MODE          debug_mode;
	bool                paused;

	int thisX = 0;
	int thisY = 0;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 1;
	float posX = 0;
	float posY = 0;
	float posZ = 0;
	bool LeftButtonOn = false;
	bool RightButtonOn = false;

	void                recurse(int depth);
	void render_scene(double currentTime, bool from_light);
};

void ray_and_shadow::startup()
{
	int i;
	load_shaders();

	static const char * const object_names[] =
	{
		"../media/objects/dragon.sbm",
		"../media/objects/sphere.sbm",
		"../media/objects/cube.sbm",
		"../media/objects/torus.sbm"
	};

	for (i = 0; i < OBJECT_COUNT; i++)
	{
		objects[i].obj.load(object_names[i]);
	}

	glGenFramebuffers(1, &depth_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);

	glGenTextures(1, &depth_tex);
	glBindTexture(GL_TEXTURE_2D, depth_tex);
	glTexStorage2D(GL_TEXTURE_2D, 11, GL_DEPTH_COMPONENT32F, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_tex, 0);

	glGenTextures(1, &depth_debug_tex);
	glBindTexture(GL_TEXTURE_2D, depth_debug_tex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, depth_debug_tex, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//////////////////////////////////////////////////////////
	glGenBuffers(1, &uniforms_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, uniforms_buffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(uniforms_block), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &sphere_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, sphere_buffer);
	glBufferData(GL_UNIFORM_BUFFER, NUMBER * sizeof(sphere), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &plane_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, plane_buffer);
	glBufferData(GL_UNIFORM_BUFFER, NUMBER * sizeof(plane), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &light_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, light_buffer);
	glBufferData(GL_UNIFORM_BUFFER, NUMBER * sizeof(sphere), NULL, GL_DYNAMIC_DRAW);

	glEnable(GL_DEPTH_TEST); //sm

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenFramebuffers(MAX_RECURSION_DEPTH, ray_fbo);
	glGenTextures(1, &tex_composite);
	glGenTextures(MAX_RECURSION_DEPTH, tex_position);
	glGenTextures(MAX_RECURSION_DEPTH, tex_reflected);
	glGenTextures(MAX_RECURSION_DEPTH, tex_refracted);
	glGenTextures(MAX_RECURSION_DEPTH, tex_reflection_intensity);
	glGenTextures(MAX_RECURSION_DEPTH, tex_refraction_intensity);

	glBindTexture(GL_TEXTURE_2D, tex_composite);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT);

	for (i = 0; i < MAX_RECURSION_DEPTH; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ray_fbo[i]);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex_composite, 0);

		glBindTexture(GL_TEXTURE_2D, tex_position[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, MAX_FB_WIDTH, MAX_FB_HEIGHT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, tex_position[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_reflected[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, tex_reflected[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_refracted[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, tex_refracted[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_reflection_intensity[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, tex_reflection_intensity[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_refraction_intensity[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, tex_refraction_intensity[i], 0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void ray_and_shadow::render(double currentTime)
{
	static const GLfloat zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	static const GLfloat ones[] = { 1.0f };
	static double last_time = 0.0;
	static double total_time = 0.0;

	if (!paused)
		total_time += (currentTime - last_time);
	last_time = currentTime;

	float f = (float)total_time;

	//vmath::vec3 view_position = vmath::vec3(sinf(1 * 0.3234f) * 28.0f, cosf(1 * 0.4234f) * 28.0f, cosf(1 * 0.1234f) * 28.0f); // sinf(f * 0.2341f) * 20.0f - 8.0f);
	//vmath::vec3 lookat_point = vmath::vec3(sinf(f * 0.214f) * 8.0f, cosf(f * 0.153f) * 8.0f, sinf(f * 0.734f) * 8.0f);
	//vmath::vec3 view_position = vmath::vec3(0, 0, 20.0f);
	/*rotZ = sqrtf(10 * 10
	- 10 * sinf(rotX / 400 * 3.14 / 2) * 10 * sinf(rotX / 400 * 3.14 / 2)
	- 10 * sinf(rotY / 400 * 3.14 / 2) * 10 * sinf(rotY / 400 * 3.14 / 2)
	);*/
	vmath::vec3 light_position = vmath::vec3(20.0f, 20.0f, 20.0f); //
	vmath::vec3 view_position = vmath::vec3(posX, posY, posZ);
	vmath::vec3 lookat_point = vmath::vec3(posX + sinf(rotX / 400 * 3.14 / 2),
		posY,//posY + 10 * sinf(rotY / 400 * 3.14 / 2),
		posZ + cosf(rotX / 400 * 3.14 / 2)//posZ-rotZ
	);
	vmath::mat4 view_matrix = vmath::lookat(view_position,
		lookat_point,
		vmath::vec3(0.0f, 1.0f, 0.0f));
	camera_view_matrix = view_matrix;
	// perspective(fovy_시야각, aspect_방향_관점_면->화면비율, n, f)
	camera_proj_matrix = vmath::perspective(100.0f,
		(float)info.windowWidth / (float)info.windowHeight,
		10.0f,
		1000.0f);

	light_proj_matrix = vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 200.0f);
	/*light_view_matrix = vmath::lookat(light_position,
		vmath::vec3(0.0f), vmath::vec3(0.0f, 1.0f, 0.0f));*/
	light_view_matrix = view_matrix;

	objects[0].model_matrix = vmath::rotate((f + 30.0f) * 14.5f, 0.0f, 1.0f, 0.0f) *
		vmath::rotate(20.0f, 1.0f, 0.0f, 0.0f) *
		vmath::translate(0.0f, -4.0f, 0.0f);

	objects[1].model_matrix = vmath::rotate((f + 30.0f) * 3.7f, 0.0f, 1.0f, 0.0f) *
		vmath::translate(sinf((f + 30.0f) * 0.37f) * 12.0f, cosf((f + 30.0f) * 0.37f) * 12.0f, 0.0f) *
		vmath::scale(2.0f);

	objects[2].model_matrix = vmath::rotate((f + 30.0f) * 6.45f, 0.0f, 1.0f, 0.0f) *
		vmath::translate(sinf((f + 30.0f) * 0.25f) * 10.0f, cosf((f + 30.0f) * 0.25f) * 10.0f, 0.0f) *
		vmath::rotate((f + 30.0f) * 99.0f, 0.0f, 0.0f, 1.0f) *
		vmath::scale(2.0f);

	objects[3].model_matrix = vmath::rotate((f + 30.0f) * 5.25f, 0.0f, 1.0f, 0.0f) *
		vmath::translate(sinf((f + 30.0f) * 0.51f) * 14.0f, cosf((f + 30.0f) * 0.51f) * 14.0f, 0.0f) *
		vmath::rotate((f + 30.0f) * 120.3f, 0.707106f, 0.0f, 0.707106f) *
		vmath::scale(2.0f);

	glEnable(GL_DEPTH_TEST);
	render_scene(total_time, true);

	if (mode == RENDER_DEPTH)
	{
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(vao);
		glUseProgram(show_light_depth_program);
		glBindTexture(GL_TEXTURE_2D, depth_debug_tex);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	else
	{
		render_scene(total_time, false);
	}

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms_buffer);
	uniforms_block * block = (uniforms_block *)glMapBufferRange(GL_UNIFORM_BUFFER,
		0,
		sizeof(uniforms_block),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	vmath::mat4 model_matrix = vmath::scale(7.0f);

	// f = 0.0f;

	block->mv_matrix = view_matrix * model_matrix;
	block->view_matrix = view_matrix;
	block->proj_matrix = vmath::perspective(50.0f,
		(float)info.windowWidth / (float)info.windowHeight,
		0.1f,
		1000.0f);

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	glBindBufferBase(GL_UNIFORM_BUFFER, 1, sphere_buffer);
	sphere * s = (sphere *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, NUMBER * sizeof(sphere), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	int i;

	for (i = 0; i < NUMBER; i++)
	{
		// float f = 0.0f;
		float fi = (float)i / (float)NUMBER;
		s[i].center = vmath::vec3(sinf(fi * 123.0f + f) * 15.75f, cosf(fi * 456.0f + f) * 15.75f, (sinf(fi * 300.0f + f) * cosf(fi * 200.0f + f)) * 20.0f);
		s[i].radius = fi * 2.3f + 3.5f;
		float r = fi * 61.0f;
		float g = r + 0.25f;
		float b = g + 0.25f;
		r = (r - floorf(r)) * 0.8f + 0.2f;
		g = (g - floorf(g)) * 0.8f + 0.2f;
		b = (b - floorf(b)) * 0.8f + 0.2f;
		s[i].color = vmath::vec4(r, g, b, 1.0f);
	}

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	glBindBufferBase(GL_UNIFORM_BUFFER, 2, plane_buffer);
	plane * p = (plane *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, NUMBER * sizeof(plane), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	//for (i = 0; i < 1; i++)
	{
		p[0].normal = vmath::vec3(0.0f, 0.0f, -1.0f);
		p[0].d = 30.0f;

		p[1].normal = vmath::vec3(0.0f, 0.0f, 1.0f);
		p[1].d = 30.0f;

		p[2].normal = vmath::vec3(-1.0f, 0.0f, 0.0f);
		p[2].d = 30.0f;

		p[3].normal = vmath::vec3(1.0f, 0.0f, 0.0f);
		p[3].d = 30.0f;

		p[4].normal = vmath::vec3(0.0f, -1.0f, 0.0f);
		p[4].d = 30.0f;

		p[5].normal = vmath::vec3(0.0f, 1.0f, 0.0f);
		p[5].d = 30.0f;
	}

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	glBindBufferBase(GL_UNIFORM_BUFFER, 3, light_buffer);
	light * l = (light *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, NUMBER * sizeof(light), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	f *= 1.0f;

	for (i = 0; i < NUMBER; i++)
	{
		float fi = 3.33f - (float)i; //  / 35.0f;
		l[i].position = vmath::vec3(sinf(fi * 2.0f - f) * 15.75f,
			cosf(fi * 5.0f - f) * 5.75f,
			(sinf(fi * 3.0f - f) * cosf(fi * 2.5f - f)) * 19.4f);
	}

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	glBindVertexArray(vao);
	glViewport(0, 0, info.windowWidth, info.windowHeight);

	glUseProgram(prepare_program);
	glUniformMatrix4fv(uniforms.ray_lookat, 1, GL_FALSE, view_matrix);
	glUniform3fv(uniforms.ray_origin, 1, view_position);
	glUniform1f(uniforms.aspect, (float)info.windowHeight / (float)info.windowWidth);
	glBindFramebuffer(GL_FRAMEBUFFER, ray_fbo[0]);
	static const GLenum draw_buffers[] =
	{
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4,
		GL_COLOR_ATTACHMENT5
	};
	glDrawBuffers(6, draw_buffers);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glUseProgram(trace_program);
	recurse(0);

	glUseProgram(blit_program);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);

	glActiveTexture(GL_TEXTURE0);
	switch (debug_mode)
	{
	case DEBUG_NONE:
		glBindTexture(GL_TEXTURE_2D, tex_composite);
		break;
	case DEBUG_REFLECTED:
		glBindTexture(GL_TEXTURE_2D, tex_reflected[debug_depth]);
		break;
	case DEBUG_REFRACTED:
		glBindTexture(GL_TEXTURE_2D, tex_refracted[debug_depth]);
		break;
	case DEBUG_REFLECTED_COLOR:
		glBindTexture(GL_TEXTURE_2D, tex_reflection_intensity[debug_depth]);
		break;
	case DEBUG_REFRACTED_COLOR:
		glBindTexture(GL_TEXTURE_2D, tex_refraction_intensity[debug_depth]);
		break;
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	/*
	glClearBufferfv(GL_COLOR, 0, gray);
	glClearBufferfv(GL_DEPTH, 0, ones);


	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	*/
}

void ray_and_shadow::render_scene(double currentTime, bool from_light)
{
	static const GLfloat ones[] = { 1.0f };
	static const GLfloat zero[] = { 0.0f };
	static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	static const vmath::mat4 scale_bias_matrix = vmath::mat4(vmath::vec4(0.5f, 0.0f, 0.0f, 0.0f),
		vmath::vec4(0.0f, 0.5f, 0.0f, 0.0f),
		vmath::vec4(0.0f, 0.0f, 0.5f, 0.0f),
		vmath::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	vmath::mat4 light_vp_matrix = light_proj_matrix * light_view_matrix;
	vmath::mat4 shadow_sbpv_matrix = scale_bias_matrix * light_proj_matrix * light_view_matrix;

	if (from_light)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
		glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(4.0f, 4.0f);
		glUseProgram(light_program);
		static const GLenum buffs[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffs);
		glClearBufferfv(GL_COLOR, 0, zero);
	}
	else
	{
		glViewport(0, 0, info.windowWidth, info.windowHeight);
		glClearBufferfv(GL_COLOR, 0, gray);
		glUseProgram(view_program);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
		glUniformMatrix4fv(smuniforms.view.proj_matrix, 1, GL_FALSE, camera_proj_matrix);
		//glUniformMatrix4fv(uniforms.ray_lookat, 1, GL_FALSE, camera_proj_matrix);
		glDrawBuffer(GL_BACK);
	}

	glClearBufferfv(GL_DEPTH, 0, ones);

	int i;
	for (i = 0; i < 4; i++)
	{
		vmath::mat4& model_matrix = objects[i].model_matrix;
		if (from_light)
		{
			glUniformMatrix4fv(smuniforms.light.mvp, 1, GL_FALSE, light_vp_matrix * objects[i].model_matrix);
		}
		else
		{
			vmath::mat4 shadow_matrix = shadow_sbpv_matrix * model_matrix;
			glUniformMatrix4fv(smuniforms.view.shadow_matrix, 1, GL_FALSE, shadow_matrix);
			glUniformMatrix4fv(smuniforms.view.mv_matrix, 1, GL_FALSE, camera_view_matrix * objects[i].model_matrix);
			glUniform1i(smuniforms.view.full_shading, mode == RENDER_FULL ? 1 : 0);
		}
		objects[i].obj.render();
	}

	if (from_light)
	{
		glDisable(GL_POLYGON_OFFSET_FILL);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void ray_and_shadow::recurse(int depth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, ray_fbo[depth + 1]);

	static const GLenum draw_buffers[] =
	{
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4,
		GL_COLOR_ATTACHMENT5
	};
	glDrawBuffers(6, draw_buffers);

	glEnablei(GL_BLEND, 0);
	glBlendFunci(0, GL_ONE, GL_ONE);

	// static const float zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// glClearBufferfv(GL_COLOR, 0, zeros);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_position[depth]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_reflected[depth]);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex_reflection_intensity[depth]);

	// Render
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (depth != (max_depth - 1))
	{
		recurse(depth + 1);
	}
	//*/

	/*
	if (depth != 0)
	{
	glBindTexture(GL_TEXTURE_2D, tex_refracted[depth]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex_refraction_intensity[depth]);

	// Render
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (depth != (max_depth - 1))
	{
	recurse(depth + 1);
	}
	}
	//**/

	glDisablei(GL_BLEND, 0);
}

void ray_and_shadow::onKey(int key, int action)
{
	if (action)
	{
		switch (key)
		{
		case GLFW_KEY_KP_ADD:
			max_depth++;
			if (max_depth > MAX_RECURSION_DEPTH)
				max_depth = MAX_RECURSION_DEPTH;
			break;
		case GLFW_KEY_KP_SUBTRACT:
			max_depth--;
			if (max_depth < 1)
				max_depth = 1;
			break;
		case '1':
			mode = RENDER_FULL;
			break;
		case '2':
			mode = RENDER_LIGHT;
			break;
		case '3':
			mode = RENDER_DEPTH;
			break;
		case 'P':
			paused = !paused;
			break;
		case 'R':
			load_shaders();
			break;
		case 'Q':
			debug_mode = DEBUG_NONE;
			break;
		case 'W':
			debug_mode = DEBUG_REFLECTED;
			break;
		case 'E':
			debug_mode = DEBUG_REFRACTED;
			break;
		case 'S':
			debug_mode = DEBUG_REFLECTED_COLOR;
			break;
		case 'D':
			debug_mode = DEBUG_REFRACTED_COLOR;
			break;
		case 'A':
			debug_depth++;
			if (debug_depth > MAX_RECURSION_DEPTH)
				debug_depth = MAX_RECURSION_DEPTH;
			break;
		case 'Z':
			debug_depth--;
			if (debug_depth < 0)
				debug_depth = 0;
			break;
		}
	}
}

void ray_and_shadow::onMouseButton(int button, int action)
{
	if (action == 1)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
			LeftButtonOn = true;
			break;
		case GLFW_MOUSE_BUTTON_2:
			RightButtonOn = true;
			break;
		case GLFW_MOUSE_BUTTON_3:
			rotX = 0;
			rotY = 0;
			rotZ = 1;
			posX = 0;
			posY = 0;
			posZ = 0;
		default:
			break;
		};
	}
	else
	{
		LeftButtonOn = false;
		RightButtonOn = false;
	}
}

void ray_and_shadow::onMouseWheel(int pos)
{
	if (pos > 0)
		//posZ += 1;
	{
		posX += sinf(rotX / 400 * 3.14 / 2);
		posZ += cosf(rotX / 400 * 3.14 / 2);
	}
	else if (pos < 0)
		//posZ -= 1;
	{
		posX -= sinf(rotX / 400 * 3.14 / 2);
		posZ -= cosf(rotX / 400 * 3.14 / 2);
	}
}

void ray_and_shadow::onMouseMove(int x, int y)
{
	if (LeftButtonOn)
	{
		if (thisX > x)
			//posX -= 1;
			posX += 2 * sinf(rotX / 400 * 3.14 / 2);
		else if (thisX < x)
			//posX += 1;
			posX -= 2 * sinf(rotX / 400 * 3.14 / 2);
		if (thisY > y)
			posY += 1;
		else if (thisY < y)
			posY -= 1;
		thisX = x;
		thisY = y;
		//printf("(%d, %d)\n", thisX, thisY);
	}

	else if (RightButtonOn)
	{
		if (thisX < x)
		{
			rotX += thisX - x;
			//if (rotX <= -400) rotX = -400;
		}
		else if (thisX > x)
		{
			rotX += thisX - x;
			//if (rotX >= 400) rotX = 400;
		}
		if (thisY < y)
		{
			rotY += thisY - y;
			//if (rotY <= -400) rotY = -400;			
		}
		else if (thisY > y)
		{
			rotY += thisY - y;
			//if (rotY >= 400) rotY = 400;
		}
		thisX = x;
		thisY = y;
	}

	else
	{
		thisX = x;
		thisY = y;
	}
}

void ray_and_shadow::load_shaders()
{
	GLuint      shaders[2];

	shaders[0] = sb7::shader::load("../media/shaders/raytracer/trace-prepare.vs.glsl", GL_VERTEX_SHADER);
	shaders[1] = sb7::shader::load("../media/shaders/raytracer/trace-prepare.fs.glsl", GL_FRAGMENT_SHADER);

	if (prepare_program != 0)
		glDeleteProgram(prepare_program);

	prepare_program = sb7::program::link_from_shaders(shaders, 2, true);

	uniforms.ray_origin = glGetUniformLocation(prepare_program, "ray_origin");
	uniforms.ray_lookat = glGetUniformLocation(prepare_program, "ray_lookat");
	uniforms.aspect = glGetUniformLocation(prepare_program, "aspect");

	shaders[0] = sb7::shader::load("../media/shaders/raytracer/raytracer.vs.glsl", GL_VERTEX_SHADER);
	shaders[1] = sb7::shader::load("../media/shaders/raytracer/raytracer.fs.glsl", GL_FRAGMENT_SHADER);

	if (trace_program)
		glDeleteProgram(trace_program);

	trace_program = sb7::program::link_from_shaders(shaders, 2, true);

	shaders[0] = sb7::shader::load("../media/shaders/raytracer/blit.vs.glsl", GL_VERTEX_SHADER);
	shaders[1] = sb7::shader::load("../media/shaders/raytracer/blit.fs.glsl", GL_FRAGMENT_SHADER);

	if (blit_program)
		glDeleteProgram(blit_program);

	blit_program = sb7::program::link_from_shaders(shaders, 2, true);

	GLuint vs;
	GLuint fs;

	vs = sb7::shader::load("../media/shaders/shadowmapping/shadowmapping-light.vs.glsl", GL_VERTEX_SHADER);
	fs = sb7::shader::load("../media/shaders/shadowmapping/shadowmapping-light.fs.glsl", GL_FRAGMENT_SHADER);

	if (light_program)
		glDeleteProgram(light_program);

	light_program = glCreateProgram();
	glAttachShader(light_program, vs);
	glAttachShader(light_program, fs);
	glLinkProgram(light_program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	smuniforms.light.mvp = glGetUniformLocation(light_program, "mvp");

	vs = sb7::shader::load("../media/shaders/shadowmapping/shadowmapping-camera.vs.glsl", GL_VERTEX_SHADER);
	fs = sb7::shader::load("../media/shaders/shadowmapping/shadowmapping-camera.fs.glsl", GL_FRAGMENT_SHADER);

	if (light_program)
		glDeleteProgram(view_program);

	view_program = glCreateProgram();
	glAttachShader(view_program, vs);
	glAttachShader(view_program, fs);
	glLinkProgram(view_program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	smuniforms.view.proj_matrix = glGetUniformLocation(view_program, "proj_matrix");
	smuniforms.view.mv_matrix = glGetUniformLocation(view_program, "mv_matrix");
	smuniforms.view.shadow_matrix = glGetUniformLocation(view_program, "shadow_matrix");
	smuniforms.view.full_shading = glGetUniformLocation(view_program, "full_shading");

	if (show_light_depth_program)
		glDeleteProgram(show_light_depth_program);

	show_light_depth_program = glCreateProgram();

	vs = sb7::shader::load("../media/shaders/shadowmapping/shadowmapping-light-view.vs.glsl", GL_VERTEX_SHADER);
	fs = sb7::shader::load("../media/shaders/shadowmapping/shadowmapping-light-view.fs.glsl", GL_FRAGMENT_SHADER);

	glAttachShader(show_light_depth_program, vs);
	glAttachShader(show_light_depth_program, fs);
	glLinkProgram(show_light_depth_program);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

DECLARE_MAIN(ray_and_shadow)

