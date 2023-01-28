#ifndef TILE_H
#define TILE_H

#include "Sprite.h"

class ENGINE_API Tile :public Sprite {
private:
	int id;
	bool block;
public:
	Tile(bool transparency, const char* path, Renderer* _renderer);
	~Tile();
	void SetID(int id) { this->id = id; }
	int GetID() { return id; }
	void SetBlock(bool block) { this->block = block; }
	bool GetBlock() { return block; }
};
#endif // !TILE_H

