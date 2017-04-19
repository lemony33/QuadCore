#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include <GLEW-2.0.0_x64/GL/glew.h>

namespace QuadCore
{

class Texture
{
public:
	Texture(const std::string& fileName);
	Texture(std::vector<std::string> faces);

	void Bind(unsigned int unit);

	virtual ~Texture();

	static void Reset() { glBindTexture(GL_TEXTURE_2D, 0); }	// 외부에서 텍스쳐 로딩 초기화

protected:
private:
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	GLuint m_texture;

	GLuint SkyBoxTexture;
	int TextureMod;
	enum
	{
		NORMAL_TEXTURE,
		SKYBOX_TEXTURE
	};
};


}

#endif