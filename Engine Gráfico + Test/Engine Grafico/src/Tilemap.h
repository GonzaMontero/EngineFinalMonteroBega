#ifndef TILEMAP_H

#include "Tile.h"
#include "Sprite.h"
#include "TextureImporter.h"
#include "renderer.h"
//#include ""

#include <vector>

class ENGINE_API Tilemap {
private:
	TextureImporter *tex;
	vector<Tile*> tiles;
	vector<vector<vector<int>>> grid;
	Renderer* rend;
	int tilemapWidth = 5;
	int tilemapHeight = 5;
	int tileWidth = 1;
	int tileHeight = 1;
public:
	Tilemap();
	~Tilemap();
	void LoadTileMap(const char* filepath);
	void LoadTile(const char* filepath);
	void DrawTileMap();
};

#endif // !TILEMAP_H