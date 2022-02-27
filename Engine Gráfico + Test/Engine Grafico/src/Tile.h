#ifndef TILE_H
#define TILE_H

#include "Sprite.h"

class ENGINE_API Tile :Sprite {
private:
	int id;
	bool block;
public:
	void SetID(int id) { this->id = id; }
	int GetID() { return id; }
	void SetBlock(bool block) { this->block = block; }
	bool GetBlock() { return block; }
};
#endif // !TILE_H

