#include "Tilemap.h"
#include "../xml_lib/tinyxml2.h"
#include <sstream>


using namespace tinyxml2;
using namespace Engine;

Tilemap::Tilemap(glm::ivec2 dimension, const char* imagePath, Shader shader, Renderer* renderer) {
	_mapDims = dimension;
	_imagePath = imagePath;
	_shader = shader;
	_renderer = renderer;
	_textureImporter = new TextureImporter();
	_collisionManager = new CollisionManager();
}

Tilemap::Tilemap() {
	_mapDims = glm::ivec2(0, 0);
	_imagePath = "";
	_renderer = nullptr;
	_textureImporter = nullptr;
	_collisionManager = nullptr;
}

Tilemap::~Tilemap() {
	if (!_grid.empty())
		_grid.clear();

	if (!_tiles.empty()) {
		for (int i = 0; i < _tiles.size(); i++) {
			for (int j = 0; j < _tiles[i].size(); j++) {
				for (int k = 0; k < _tiles[i][j].size(); k++) {
					if (_tiles[i][j][k]) {
						delete _tiles[i][j][k];
						_tiles[i][j][k] = NULL;
					}
				}
			}
		}
		_tiles.clear();
	}

	if (_textureImporter != NULL) {
		delete _textureImporter;
		_textureImporter = NULL;
	}

	if (_collisionManager != NULL) {
		delete _collisionManager;
		_collisionManager = NULL;
	}
}

void Tilemap::SetImagePath(const char* path) {
	_imagePath = path;
}

void Tilemap::LoadMap(const char* path) {
	//Se carga el mapa a travez de tinyxml usando el path
	tinyxml2::XMLDocument doc;

	doc.LoadFile(path);

	//Se crean los punteros y as� se obtienen los elementos del archivo xml que se carg� con path
	tinyxml2::XMLElement* p_root_element = doc.FirstChildElement("map");

	if (p_root_element == NULL) {
		std::cout << "Error loading tilemap" << std::endl;
		return;
	}

	//Se almacena width y height a su vez se setea el width y height de cada tile
	int width = p_root_element->IntAttribute("width");
	int height = p_root_element->IntAttribute("height");
	_tileWidth = p_root_element->IntAttribute("tilewidth");
	_tileHeight = p_root_element->IntAttribute("tileheight");

	_layerDims.x = width;
	_layerDims.y = height;

	//Se buscan los layers del mapa
	int layerCount = 0;
	std::vector<tinyxml2::XMLElement*> layerElement;
	for (tinyxml2::XMLElement* childElement = p_root_element->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement()) {
		string childName = childElement->Name();
		string layer = "layer";
		if (childElement != NULL && childName == layer) {
			layerCount++;
			layerElement.push_back(childElement);
		}

	}
	std::cout << "cantidad de layers cargados desde archivo: " << layerCount << std::endl;
	_grid.resize(layerCount); //Se actualiza el tama�o del vector al numero de layers encontrados
	for (int l = 0; l < _grid.size(); l++) {
		tinyxml2::XMLText* dataElement = layerElement[l]->FirstChildElement("data")->FirstChild()->ToText();
		if (dataElement == NULL) {
			std::cout << "Error loading tilemap" << std::endl;
			return;
		}

		//El segundo vector que representa a Y se llena con datos encontrados dentro de data (hijo)
		//Lo mismo ocurre con el vector que representa X.
		std::string mapGrid;
		mapGrid = dataElement->Value();
		std::stringstream ss(mapGrid); //Se crea un string stream en donde se almacenan los ids de cada layer
		_grid[l].resize(height);
		for (int y = 0; y < height; y++) {
			_grid[l][y].resize(width);
			for (int x = 0; x < width; x++) {
				std::string value;
				std::getline(ss, value, ',');
				if (!ss.good())
					break;

				int val;
				if (std::stringstream(value) >> val) //String stream usa string buffer para operar con secuencias de caracteres
					_grid[l][y][x] = val;

				_tilesAmount++;
			}
		}
	}

	doc.Clear();
	LoadMapFromGrid();
}

void Tilemap::SetTilesInfo(const char* path) {
	_tilesInfoPath = path;
}

void Tilemap::LoadMapFromGrid() {
	_textureImporter->SetPath(_imagePath); //Se settea el path de _textureImporter a _imagePath
	_textureImporter->LoadImage(_mapWidth, _mapHeight, true); //se carga la imagen con esos parametros de alto, ancho y transparencia
	int xPos = _tileWidth;
	std::cout << "tile width: " << _tileWidth << std::endl;
	int yPos = 700;
	float z = 0;
	int actualID = 0;
	_tiles.resize(_grid.size()); //se hace que el tama�o de los tiles sea igual al del grid

	for (int l = 0; l < _grid.size(); l++) {  //este for carga las tiles 1 a 1, se la cream setea el render, shader, path, etc y se pasa a la siguiente
		xPos = _tileWidth;
		yPos = 700;
		_tiles[l].resize(_grid[l].size());
		for (int y = 0; y < _grid[l].size(); y++) {
			_tiles[l][y].resize(_grid[l][y].size());
			for (int x = 0; x < _grid[l][y].size(); x++) {
				Tile* newTile = new Tile(_grid[l][y][x], false, _tileWidth, _tileHeight, _renderer);
				newTile->SetRenderer(_renderer);
				newTile->SetShader(_shader);
				newTile->SetPath(_imagePath);
				newTile->Init();
				newTile->Translate(xPos, yPos, z);
				newTile->Scale(_tileWidth, _tileHeight, 1);
				newTile->SetUVs(GetTileFromID(newTile->GetID()));

				if (newTile->GetID() <= 0 && l > 0) {
					delete newTile;
					newTile = NULL;
					xPos += _tileWidth + _tileWidth;
				}
				else {
					if (newTile->GetID() > 0 && l > 0) {
						newTile->SetID(newTile->GetID() - actualID);
					}
					newTile->SetIsWalkable(_tilesInfoPath);
					newTile->SetUVs(GetTileFromID(newTile->GetID()));
					_tiles[l][y][x] = newTile;
					xPos += newTile->transform.scale.x + _tileWidth;
				}
			}
			
			z += 0.001f;
			yPos -= _tileHeight + _tileHeight;
			xPos = _tileWidth;
			actualID = 1;
		}
	}
	std::cout << "Cantidad de layers: " << _tiles.size() << endl;
}

glm::vec4 Tilemap::GetTileFromID(unsigned int id) { //devuelve el UV de un tile especifico usando como parametro su ID
	int xTile = id % _mapDims.x;
	int yTile = id / _mapDims.x;
	yTile = _mapHeight - yTile - 1;
	std::cout << "xTile: " << xTile << std::endl;
	std::cout << "yTile: " << yTile << std::endl;

	glm::vec4 uv = glm::vec4(0, 0, 0, 0);

	uv.x = xTile / static_cast<float>(_mapDims.x);
	uv.y = yTile / static_cast<float>(_mapDims.y);
	uv.z = 1.0f / (_mapDims.x);
	uv.w = 1.0f / (_mapDims.y);

	return uv;
}

void Tilemap::Draw() {  //Dibuja cada tile usando la funcion heredada de DrawSprite
	if (!_tiles.empty()) {
		for (int i = 0; i < _tiles.size(); i++) {
			for (int j = 0; j < _tiles[i].size(); j++) {
				for (int k = 0; k < _tiles[i][j].size(); k++) {
					if (_tiles[i][j][k]) {
						_tiles[i][j][k]->DrawSprite();
					}
				}
			}
		}
	}
}

void Tilemap::CheckCollisionWithTileMap(Entity2D* entity, glm::vec3 entityPosition, float speed) { 
	//setea todos los valores a tener en cuenta para una colision en el tilemap
	float distanceWithTilemapX = glm::distance(glm::vec2(entityPosition.x, 0), glm::vec2(0, 0));
	float distanceWithTilemapWidth = glm::distance(glm::vec2(entityPosition.x + entity->transform.scale.x * 0.5f, 0), glm::vec2(0, 0));
	float distanceWithTilemapY = glm::distance(glm::vec2(0, entityPosition.y), glm::vec2(0, 700));
	float distanceeWithTilemapHeight = glm::distance(glm::vec2(0, entityPosition.y - entity->transform.scale.y * 0.5f), glm::vec2(0, 700));

	float indexInX = distanceWithTilemapX / _tileWidth * 0.5f;
	float indexInY = distanceWithTilemapY / _tileHeight * 0.5f;
	float indexInWidth = distanceWithTilemapWidth / _tileWidth * 0.5f;
	float indexInHeight = distanceeWithTilemapHeight / _tileHeight * 0.5f;

	int rightTile = static_cast<int>(indexInWidth) + 1;
	int leftTile = static_cast<int>(indexInX) - 1;
	int topTile = static_cast<int>(indexInY) - 1;
	int bottomTile = static_cast<int>(indexInHeight) + 1;

	//Se marca en consola cuales son los tiles que rodean a entity, en este caso el player.
	std::cout << "rightTile: " << rightTile << std::endl;
	std::cout << "leftTile: " << leftTile << std::endl;
	std::cout << "topTile: " << topTile << std::endl;
	std::cout << "bottomTile: " << bottomTile << std::endl;

	//Se revisan si las tiles cercanas son walkable
	for (int i = leftTile; i <= rightTile; i++) {
		for (int j = topTile; j <= bottomTile; j++) {
			for (int l = 0; l < _grid.size(); l++) {
				if (i >= 0 && i <= _layerDims.x - 1 && j >= 0 && j <= _layerDims.y - 1 && l >= 0) {
					Tile* t = _tiles[l][j][i];
					if (t != NULL && !t->GetIsWalkable()) {
						_collisionManager->CheckCollision(entity, t, speed);
					}
				}
			}
		}
	}
}
