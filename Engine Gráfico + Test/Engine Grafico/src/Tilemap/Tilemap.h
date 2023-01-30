#ifndef TILEMAP_H

#include "../Utils/Export.h"
#include "../Shader/Shader.h"
#include "../Renderer/renderer.h"
#include "../Collision/Collision Manager.h"
#include "../Utils/TextureImporter.h"
#include "Tile.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Engine {
	class ENGINE_API Tilemap {
	private:
		std::vector<std::vector<std::vector<Tile*>>> _tiles;
		std::vector<std::vector<std::vector<int>>> _grid;
		glm::ivec2 _mapDims;
		glm::ivec2 _layerDims;
		Shader _shader;
		Renderer* _renderer = nullptr;
		TextureImporter* _textureImporter = nullptr;
		CollisionManager* _collisionManager = nullptr;
		const char* _imagePath;
		const char* _tilesInfoPath;
		Tile* _actualTile = nullptr;

		int _tileWidth;
		int _tileHeight;
		int _mapWidth;
		int _mapHeight;
		int _tilesAmount;

	public:
		Tilemap();
		Tilemap(glm::ivec2 dimension, const char* imagePath, Shader shader, Renderer* renderer);
		~Tilemap();
		void SetImagePath(const char* path);
		void LoadMap(const char* path);
		void SetTilesInfo(const char* path);
		void LoadMapFromGrid();
		glm::vec4 GetTileFromID(unsigned int id);
		void Draw();
		void CheckCollisionWithTileMap(Entity2D* entity, glm::vec3 entityPosition, float speed);
	};
}

#endif // !TILEMAP_H