#include "textureImporter.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
TextureData TextureImporter::ImportTexture(const char* filePath)
{
	TextureData textureData;
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &textureData.texture);
	glBindTexture(GL_TEXTURE_2D, textureData.texture);
	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	textureData.pixelData = stbi_load(filePath, &textureData.width, &textureData.height, &textureData.nrChannels, STBI_rgb_alpha);
	if (textureData.pixelData) {
		if(textureData.nrChannels != 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.pixelData);
		else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureData.width, textureData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.pixelData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "Failed to import texture: pixel data null" << std::endl;
	stbi_image_free(textureData.pixelData);
	return textureData;
}

void TextureImporter::BindTexture(unsigned int data)
{
	glBindTexture(GL_TEXTURE_2D,data);
	glActiveTexture(GL_TEXTURE0);
}