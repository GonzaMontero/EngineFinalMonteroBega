#ifndef TILE_H
#define TILE_H
	//============================================
#include "sprite/Sprite.h"
//============================================
	class SlayerWxEngine_API Tile : public Sprite
	{
	public:
		Tile();
		~Tile();

		bool isWalkable();
		void walkability(bool bWalkable);

		unsigned int getId();
		void setId(unsigned int id);

	private:
		unsigned int _id;
		bool _walkable;
	};
	//============================================
#endif

//public:
//	Tile();
//	Tile(int _id);
//	~Tile();
//
//	bool GetWalkable();
//	void SetWalkeable(bool Walkeable);
//
//	unsigned int GetId();
//	void SetId(unsigned int id);
//
//	void SetTileScale(float x, float y);
//
//
//
//private:
//	unsigned int id;
//	bool isWalkeable;
//	glm::vec2 tilePosition; 
//	glm::vec2 tileScale;    
//};
//