#include "Tile.h"

Engine::Tile::Tile()
{
	_id = 0;
	_walkable = false;
}

Engine::Tile::Tile(int ID, bool walkable, Renderer* renderer, const char* imageFilePath, bool invertImage)
{
	_id = ID;
	_walkable = walkable;

	SetTexture(renderer, imageFilePath, invertImage);
}

Engine::Tile::~Tile()
{

}

bool Engine::Tile::GetWalkable()
{
	return _walkable;
}

void Engine::Tile::SetWalkable(bool walkable)
{
	_walkable = walkable;
}

unsigned int Engine::Tile::GetID()
{
	return _id;
}

void Engine::Tile::SetID(unsigned int ID)
{
	_id = ID;
}
