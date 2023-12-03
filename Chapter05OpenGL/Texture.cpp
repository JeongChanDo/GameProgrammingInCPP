#include "Texture.h"
#include <GL/glew.h>
#include <SDL.h>
#include <SOIL.h>

Texture::Texture()
	:mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{

}

Texture::~Texture()
{
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;

	unsigned char* image = SOIL_load_image(fileName.c_str(),
		&mWidth, &mHeight, &channels, SOIL_LOAD_AUTO);

	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load images %s : %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}
	// �ؽ�ó �����ϰ�, Ȱ��ȭ
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	// �̹��� -> �ؽ�ó ������Ʈ�� ����
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format,
		GL_UNSIGNED_BYTE, image);


	SOIL_free_image_data(image);
	// ���߼������͸� Ȱ��ȭ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}