#include "Texture.h"
#include"SOIL2/SOIL2.h"
#include<iostream>

Texture::Texture(const char* filePath)
{
	mTexID = SOIL_load_OGL_texture(filePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (mTexID == 0) 
	{ 
		std::cout << "テクスチャファイルが見つかりませんでした。: " << filePath << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, mTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
	{
		GLfloat anisoset = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoset);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoset);
	}
}

Texture::~Texture()
{
}

void Texture::setActive(Binding binding)
{
	glActiveTexture(binding);
	glBindTexture(GL_TEXTURE_2D, mTexID);
}
