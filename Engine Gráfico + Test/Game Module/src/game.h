#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

class Game : public BaseGame {
public:
    Game();
    ~Game();
    float valorRotacion;
	float valorEscala;
	float valorTranslateX;
	float valorTranslateY;
	Color color;
	//Shape* testShape;
	Sprite* testSprite;
	Sprite* testSprite2;
	Sprite* spriteSheet;
	Animation* spriteSheetAnim;
    void init() override;
    void updateGame() override;
    void unload() override;
}; 
#endif // !GAME_H