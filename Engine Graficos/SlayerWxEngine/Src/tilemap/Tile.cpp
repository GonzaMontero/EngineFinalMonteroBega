#include "Tile.h"
//================================================
Tile::Tile() {
	_id = 0;
	_walkable = false;
}
//================================================
Tile::~Tile() {
}
//================================================
bool Tile::isWalkable() {
	if (!_walkable)
		return false;

	else
		return true;
}
//================================================
void Tile::walkability(bool bWalkable) {
	_walkable = bWalkable;
}
//================================================
unsigned int Tile::getId() {
	return _id;
}
//================================================
void Tile::setId(unsigned int id) {
	_id = id;
}
//================================================

//Tile::Tile() : Sprite()
//{
//	id = 0;
//	isWalkeable = false;
//	tileScale = glm::vec2(0, 0);
//	tilePosition = glm::vec2(0, 0);
//}
//
//Tile::Tile(int _id) : Sprite()
//{
//	id = _id;
//	isWalkeable = false;
//	tileScale = glm::vec2(0, 0);
//	tilePosition = glm::vec2(0, 0);
//}
//
//Tile::~Tile() {
//}
//
//bool Tile::GetWalkable() {
//	return isWalkeable;
//}
//
//void Tile::SetWalkeable(bool Walkeable) {
//	isWalkeable = Walkeable;
//}
//
//unsigned int Tile::GetId() {
//	return id;
//}
//
//void Tile::SetId(unsigned int newID) {
//	id = newID;
//}
//
//void Tile::SetTileScale(float x, float y)
//{
//	tileScale = glm::vec2(x,y);
//}
//