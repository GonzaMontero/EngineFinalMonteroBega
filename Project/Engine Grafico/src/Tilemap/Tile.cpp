#include "Tile.h"

namespace Engine {
	Tile::Tile()
	{
		_id = 0;
		_walkable = false;
	}

	Tile::Tile(int ID, bool walkable, Renderer* renderer, const char* imageFilePath, bool invertImage)
	{
		_id = ID;
		_walkable = walkable;

		SetTexture(renderer, imageFilePath, invertImage);
	}

	Tile::~Tile()
	{

	}

	bool Tile::GetWalkable()
	{
		return _walkable;
	}

	void Tile::SetWalkable(bool walkable)
	{
		_walkable = walkable;
	}

	unsigned int Tile::GetID()
	{
		return _id;
	}

	void Tile::SetID(unsigned int ID)
	{
		_id = ID;
	}
}