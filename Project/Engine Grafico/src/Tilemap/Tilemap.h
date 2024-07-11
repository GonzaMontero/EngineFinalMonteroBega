#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

namespace Engine {
	class ENGINE_API Tilemap {
	public:
		Tilemap(Renderer* renderer);
		~Tilemap();

		const Tile& GetTileByID(unsigned int tileID);
		void SetTile(const Tile& tile);
		void SetMapTileID(int layer, unsigned int column, unsigned int row, unsigned int ID);

		void SetDimensions(float width, float height);
		void SetTileDimensions(float tileWidth, float tileHeight);

		void SetTexture(TextureData* texture);
		void Draw();

		bool ImportTilemap(std::string filePath);
		bool CheckCollision(Entity2D& entity);

		std::vector<Tile**> GetTileGrid();

	private:
		std::vector<Tile> _tiles;
		std::vector<Tile**> _tilesGrid;

		unsigned int _width;
		unsigned int _height;
		
		float _tileWidth;
		float _tileHeight;

		TextureData* _texture;

		float _imageWidth;
		float _imageHeight;

		float _convertedPosX;
		float _convertedPosY;

		std::string _filePath;

		Renderer* _renderer;
	};
}

#endif // !TILEMAP_H