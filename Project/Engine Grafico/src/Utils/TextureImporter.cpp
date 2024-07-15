#include "glew.h"
#include "glfw3.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../stb_image.h"

#include "TextureImporter.h"
#include <iostream>

#define STBI_FAILURE_USERMSG 


namespace Engine{
	TextureData TextureImporter::LoadTexture(const char* filePath, bool invertVertical)
	{
		unsigned int newTextureID;
		int textureWidth;
		int textureHeight;
		int numberOfChannels;

		glGenTextures(1, &newTextureID);
		glBindTexture(GL_TEXTURE_2D, newTextureID); //glgen generates the texture, while bind texture sets it as the texture to be used

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri sets what should happen when the texture size gets smaller
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(invertVertical); //OpenGL awaits inverted textures

		unsigned char* data = stbi_load(filePath, &textureWidth, &textureHeight, &numberOfChannels, 0);

		if (data)
		{
			int channelType = GL_RGB;
			switch (numberOfChannels)
			{
			case 1:
				channelType = GL_R;
				break;
			case 2:
				channelType = GL_RG;
				break;
			case 3:
				channelType = GL_RGB;
				break;
			case 4:
				channelType = GL_RGBA;
				break;
			default:
				break;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, channelType, textureWidth, textureHeight, 0, channelType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		TextureData tex = { newTextureID, textureWidth, textureHeight };

		return tex;
	}
}
