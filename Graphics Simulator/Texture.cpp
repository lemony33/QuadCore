#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

using QuadCore::Texture;

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	//glTexImage2D();
	TextureMod = NORMAL_TEXTURE;
	stbi_image_free(imageData);
}

Texture::Texture(std::vector<std::string> faces)
{
	glGenTextures(1, &SkyBoxTexture);
	
	int width, height;

	glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBoxTexture);

	for (GLuint i = 0; i < faces.size(); i++)
	{
		unsigned char* imageData = stbi_load(faces[i].c_str(), &width, &height, 0, 3);
		//image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	TextureMod = SKYBOX_TEXTURE;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	if (TextureMod == NORMAL_TEXTURE)
	{
		assert(unit >= 0 && unit <= 31);	// geo texture 0~31

		glActiveTexture(GL_TEXTURE0 + unit);

		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	else if (TextureMod == SKYBOX_TEXTURE)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBoxTexture);
	}
}