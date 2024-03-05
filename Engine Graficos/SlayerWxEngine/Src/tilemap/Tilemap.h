#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "tinyxml2.h"
#include <vector>
#include <string>

//class SlayerWxEngine_API Tilemap {
//public:
//    Tilemap(const char* tmxFilePath, const char* imageFilePath);
//    ~Tilemap();
//
//    void LoadMap(const char* tmxFilePath, const char* imageFilePath);
//    void Draw(); // Puedes implementar esta función para renderizar el mapa
//
//    void CheckCollisionWithTileMap(Entity2D* player, glm::vec3 actualPosition, float speed);
//
//    void SetDimensions(/*float width, float height*/);
//
//private:
//    std::vector<Tile> tiles;
//    std::vector<Tile**> grid;
//    int gridWidth;
//    int gridHeight;
//    float tileWidth;  
//    float tileHeight;
//    float imageWidth;
//    float imageHeight;
//    int columns = 0;
//    int rows = 0;
//    int tilesAmmount = 0;
//    std::string imagePath;
//    TextureData imageTexture;
//
//    const Tile& GetTileFromID(unsigned int uiId);
//    //void SetDimensions(float width, float height);
//    //const Tile& GetTileForIndex(unsigned int uiId);
//    ///void checkCollision(Entity2D& object);
//    //Tile* FindTileAtTextureCoordinate(float textureX, float textureY);
//    //void SetAdyacentTiles();
//    void SetPropertiesPath(const char* path, Tile* myTile);
//};
//
//#endif

class SlayerWxEngine_API Tilemap {
public:
	Tilemap();
	~Tilemap();

	const Tile& tile(unsigned int uiId);
	void setTile(const Tile& rkTile);
	void setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId);

	void setDimensions(float width, float heigth);
	void setTileDimensions(float tileWidth, float tileHeigth);

	void setTexture(const TextureData& rkTexture);
	void draw();

	bool importTileMap(std::string filePath);
	void checkCollision(Entity2D& object);
	float tilemapScale = 0.1f;
private:
	std::vector<Tile> tiles;
	std::vector<Tile**> _tileMapGrid;

	unsigned int _width;
	unsigned int _height;

	float _tileWidth;
	float _tileHeight;

	TextureData _texture;

	float _imageWidth;
	float _imageHeight;

	float convertedPosX;
	float convertedPosY;

	std::string _imagePath;
};

//public:
//    Tilemap();
//
//    void LoadMap(const char* tmxFilePath);
//
//    const Tile& GetTile(int x, int y) const {
//        return tileMap[y][x];
//    }
//
//private:
//    std::vector<std::vector<Tile>> tileMap;
//    int width;
//    int height;
//};
//
#endif