#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

class Game : public BaseGame {
public:
    Game();
    ~Game();
    float valorRotacion;
	Shape* testShape;
    void init() override;
    void updateGame() override;
    void unload() override;
};
#endif // !GAME_H