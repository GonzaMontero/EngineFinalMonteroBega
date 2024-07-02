#ifndef TEXTURE_IMPORTER
#define TEXTURE_IMPORTER

#include "Export.h"

namespace Engine {

	struct TextureData
	{
		unsigned int ID;
		float width;
		float height;
	};

	class ENGINE_API TextureImporter 
	{
	public:
		static TextureData LoadTexture(const char* filePath, bool invertVertical);
	};
}

#endif