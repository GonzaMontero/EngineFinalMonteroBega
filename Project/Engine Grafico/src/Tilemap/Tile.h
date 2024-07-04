#ifndef TILE_H
#define TILE_H

#include "../Sprite/Sprite.h"

namespace Engine {
	class ENGINE_API Tile : public Sprite {
	public:
		Tile();
		Tile(int ID, bool walkable, Renderer* renderer, const char* imageFilePath, bool invertImage);
		~Tile();

		bool GetWalkable();
		void SetWalkable(bool walkable);

		unsigned int GetID();
		void SetID(unsigned int ID);

	private:
		unsigned int _id;
		bool _walkable;
	};
}

#endif // !TILE_H

