#include "Tile.h"

Tile::Tile(bool transparency, const char* path, Renderer* _renderer): Sprite(transparency,path,_renderer)
{
	block = false;
	id = 0;
}

Tile::~Tile()
{
}
