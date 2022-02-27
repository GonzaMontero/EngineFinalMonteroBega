#include "Tilemap.h"
#include "Libraries/tinyxml2.h"
using namespace tinyxml2;

Tilemap::Tilemap()
{
	tex = new TextureImporter();
}

Tilemap::~Tilemap()
{
	if (tex != nullptr) {
		delete tex;
		tex = nullptr;
	}
	if (!tiles.empty()) {
		for (short i = 0; i < tiles.size(); i++) {
			if (tiles[i] != nullptr) {
				delete tiles[i];
				tiles[i] = nullptr;
			}
		}
		tiles.clear();
	}
	if (!grid.empty()) {
		grid.clear();
	}
}

void Tilemap::LoadTileMap(const char* filepath)
{
	XMLDocument map;
	map.LoadFile(filepath);
	XMLElement* mapElement = map.FirstChildElement("map");
	if (mapElement) {
		tileWidth = mapElement->IntAttribute("tilewidth");
		tileHeight = mapElement->IntAttribute("tileheight");
		tilemapWidth = mapElement->IntAttribute("width");
		tilemapHeight = mapElement->IntAttribute("height");
	}
}

void Tilemap::LoadTile()
{

}

void Tilemap::DrawTileMap()
{

}
