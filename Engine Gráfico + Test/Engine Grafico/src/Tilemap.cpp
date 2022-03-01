#include "Tilemap.h"
#include "Libraries/tinyxml2.h"
using namespace tinyxml2;

Tilemap::Tilemap()
{
	tex = new TextureImporter();
	rend = new Renderer();
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
	else {
		cout << "Error loading tilemap :(" << endl;
		return;
	}
	int layers = 0;
	vector<XMLElement>layerElement;
	for (XMLElement* child = mapElement->FirstChildElement(); child; child = child->NextSiblingElement()) {
		string name = child->Name();
		string layer = "layer";
		if (child != nullptr && name == layer) {
			layers++;
			layerElement.push_back(*child);
		}
	}
	cout << layers << endl;
	grid.resize(layers);
	for (int i = 0; i < grid.size(); i++)
	{
		XMLText* dataElement = layerElement[i].FirstChildElement("data")->FirstChild()->ToText();
		if (dataElement == nullptr) {
			cout << "Error loading tilemap :(" << endl;
			return;
		}
		string mapGrid;
		mapGrid = dataElement->Value();
		stringstream ss(mapGrid);
		grid[i].resize(tilemapHeight);
		for (int y = 0; y < tilemapWidth; y++)
		{
			grid[i][y].resize(tilemapWidth);
			for (int x = 0; x < tilemapHeight; x++)
			{
				string value;
				getline(ss, value, ',');
				if (!ss.good())
					break;
				int val;
				if (stringstream(value) >> val)
					grid[i][y][x] = val;
				//tiles++
			}
		}
	}	
}

void Tilemap::LoadTile()
{
	tex->SetPath("../res/Tilemaps/TILES.png"); //Aca va el tileset
	tex->LoadImage(tileWidth, tileHeight, true);
	int xPos = 50;
	int yPos = 700;
	for (int l = 0; l < grid.size(); l++) {
		xPos = 50;
		yPos = 700;
		for (int y = 0; y < grid[l].size(); y++) {
			for (int x = 0; x < grid[l][y].size(); x++) {
				if (grid[l][y][x] == 21) {
					std::cout << grid[l][y][x] << std::endl;
				}
				Tile* newTile = new Tile();
				newTile->SetBlock(false);
				newTile->SetID(grid[l][y][x]);	
				newTile->SetRenderer(rend);
				newTile->SetPath("../res/Tilemaps/TILES.png");
				newTile->Init();
				newTile->Translate(xPos, yPos, 1 - 0.5f);
				newTile->SetScale(tileWidth, tileHeight,1);

				//newTile->SetShader(shader);
				if (newTile->GetID() <= 0 && l > 0) {
					delete newTile;
					newTile = NULL;
					xPos += tileWidth + tileWidth;
				}
				else {
					//newTile->SetPropertiesPath("res/tilemap/Ground.tsx"); IGNORAR
					//newTile->SetUVs(GetTileFromID(newTile->GetID() - 1));
					//tiles.push_back(newTile);
					tiles.push_back(newTile);
					xPos += newTile->scalation.x + tileWidth;
				}
			}
			yPos -= tileHeight + tileHeight;
			xPos = 50;
		}
	}
	std::cout << "Ammount of tilemap Entities: " << tiles.size() << endl;
}

void Tilemap::DrawTileMap()
{
	for (short i = 0; i < tiles.size(); i++) {
		tiles[i]->DrawSprite();
	}
}
