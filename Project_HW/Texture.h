#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GLEW-2.0.0_x64/GL/glew.h>

namespace QuadCore
{

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();

	static void Reset() { glBindTexture(GL_TEXTURE_2D, 0); }	// �ܺο��� �ؽ��� �ε� �ʱ�ȭ

protected:
private:
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	GLuint m_texture;
};


}

#endif