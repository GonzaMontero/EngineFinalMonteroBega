#include "Tilemap.h"
#include "../xml_lib/tinyxml2.h"
#include "../Utils/TextureImporter.h"

namespace Engine
{
	Tilemap::Tilemap(Renderer* renderer)
	{
		_renderer = renderer;
	}

	Tilemap::~Tilemap()
	{

	}

	const Tile& Tilemap::GetTileByID(unsigned int tileID)
	{
		Tile* noTileFound = nullptr;

		for (int i = 0; i < _tiles.size(); i++)
		{
			if (tileID == _tiles[i].GetID())			
				return _tiles[i];			
		}

		return *noTileFound;
	}

	void Tilemap::SetTile(const Tile& tile)
	{
		_tiles.push_back(tile);
	}

	void Tilemap::SetMapTileID(int layer, unsigned int column, unsigned int row, unsigned int ID)
	{
		_tilesGrid[layer][column][row] = GetTileByID(ID);
	}

	void Tilemap::SetDimensions(float width, float height)
	{
		_width = width;
		_height = height;

		Tile** tilemapTemp;

		tilemapTemp = new Tile * [height];

		for (int i = 0; i < height; i++)
		{
			tilemapTemp[i] = new Tile[width];
		}
		_tilesGrid.push_back(tilemapTemp);
	}

	void Tilemap::SetTileDimensions(float tileWidth, float tileHeight)
	{
		_tileWidth = tileWidth;
		_tileHeight = tileHeight;
	}

	void Tilemap::SetTexture(TextureData* texture)
	{
		_texture = texture;
	}

	void Tilemap::Draw()
	{
		float mapWidth = -(_width * _tileWidth) / 2.0f;
		float mapHeight = (_height * _tileHeight) / 2.0f;

		for (int i = 0; i < _tilesGrid.size(); i++)
		{
			for (int y = 0; y < _height; y++)
			{
				for (int x = 0; x < _width; x++)
				{
					if (_tilesGrid[i][y][x].GetID() != NULL)
					{
						glm::vec3 pos = glm::vec3(mapWidth + (_tileWidth * x), mapHeight - (_tileHeight * y), 0);
						_tilesGrid[i][y][x].SetPos(pos);
						_tilesGrid[i][y][x].Draw();
					}
				}
			}
		}
	}

	bool Tilemap::ImportTilemap(std::string filePath)
	{
		tinyxml2::XMLDocument document;
		tinyxml2::XMLError errorHandler;

		errorHandler = document.LoadFile(filePath.c_str());
		if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED)
			return false;

		tinyxml2::XMLElement* mapNode = document.FirstChildElement("map");
		if (mapNode == nullptr)
			return false;

		SetDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));
		SetTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight"));

		tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
		if (pTileset == NULL)
			return false;

		int tileCount = pTileset->IntAttribute("tilecount");
		int columns = pTileset->IntAttribute("columns");
		int rows = tileCount / columns;

		_filePath = "../Game Module/res/textures/";
		_filePath += pTileset->FirstChildElement("image")->Attribute("source");
		TextureData texData = TextureImporter::LoadTexture(_filePath.c_str(), true);
		SetTexture(&texData);

		_imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
		_imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");
		float tileX = 0.0f, tileY = 0.0f;
		int _id = 1;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Engine::Tile newTile;

				newTile.SetID(_id);
				newTile.SetTexture(_renderer, _filePath.c_str(), false);
				newTile.SetScale(glm::vec3(_tileWidth, _tileHeight, 1.0f));

				newTile.SetTextureCoordinates(glm::vec2((tileX + _tileWidth) / _imageWidth, tileY / _imageHeight),
					glm::vec2((tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight),
					glm::vec2(tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight),
					glm::vec2(tileX / _imageWidth, tileY / _imageHeight));

				tileX += _tileWidth;
				SetTile(newTile);
				_id++;
			}
			tileX = 0;
			tileY += _tileHeight;
		}

		tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");

		while (pTile) {
			unsigned int id = pTile->IntAttribute("id");
			tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
			std::string propertyName = pProperty->Attribute("value");
			if (propertyName == "false")
				_tiles[id].SetWalkable(false);
			else
				_tiles[id].SetWalkable(true);

			pTile = pTile->NextSiblingElement("tile");
		}

		tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
		if (pLayer == NULL)
			return false;

		int layerCount = 0;
		while (pLayer) {
			tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData == NULL)
				return false;

			if (layerCount > 0) {
				Tile** tileMap;
				tileMap = new Tile * [_height];

				for (int i = 0; i < _height; i++)
				{
					tileMap[i] = new Tile[_width];
				}

				_tilesGrid.push_back(tileMap);
			}

			while (pData) {
				std::vector<int> tileGids;
				for (tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
					pTile != NULL;
					pTile = pTile->NextSiblingElement("tile"))
				{
					unsigned int gid = std::atoi(pTile->Attribute("gid")); // tile's id is saved
					tileGids.push_back(gid);
				}

				int gid = 0;
				for (int y = 0; y < _height; y++) {
					for (int x = 0; x < _width; x++) {
						if (tileGids[gid] != 0)
							SetMapTileID(layerCount, y, x, tileGids[gid]);
						gid++;
					}
				}

				pData = pData->NextSiblingElement("data");
			}
			layerCount++;
			pLayer = pLayer->NextSiblingElement("layer");
		}

		return true;
	}

	bool Tilemap::CheckCollision(Entity2D& entity)
	{
		_convertedPosX = entity.GetTransform().position.x + (_width / 2.0f) * _tileWidth;
		_convertedPosY = entity.GetTransform().position.y + (_height / 2.0f) * _tileHeight;


		int leftTile = _convertedPosX / _tileWidth;
		int rightTile = (_convertedPosX + entity.GetTransform().scale.x) / _tileWidth;

		int topTile = (_convertedPosY / _tileHeight) * -1;
		int bottomTile = ((_convertedPosY - entity.GetTransform().scale.y) / _tileHeight) * -1;

		if (leftTile < 0)
			leftTile = 0;

		if (rightTile >= _width)
			rightTile = _width - 1;

		if (topTile < 0)
			topTile = 0;

		if (bottomTile >= _height)
			bottomTile = _height - 1;

		for (int i = leftTile; i <= rightTile; i++)
		{
			for (int j = topTile; j <= bottomTile; j++)
			{
				for (int k = 0; k < _tilesGrid.size(); k++)
				{
					if (!_tilesGrid[k][j][i].GetWalkable())
					{
						float overlapX = 0;
						float overlapY = 0;

						CollisionDirection collisionDirection = entity.CheckCollision(_tilesGrid[k][j][i], overlapX, overlapY);

						if (collisionDirection != CollisionDirection::NONE)
						{
							entity.ApplyCollisionRestriction(collisionDirection, overlapX, overlapY, false);
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	std::vector<Tile**> Tilemap::GetTileGrid()
	{
		return _tilesGrid;
	}
}