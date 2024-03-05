#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H
struct TextureData
{
	unsigned char* pixelData;
	int width;
	int height;
	int nrChannels;
	unsigned int texture;
};

class TextureImporter {
private:

public:
	static TextureData ImportTexture(const char* filePath);
	static void BindTexture(unsigned int data);
};

#endif