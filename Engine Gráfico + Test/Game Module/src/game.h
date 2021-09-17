#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

class Game : public BaseGame {
public:
    Game();
    ~Game();
    void init() override;
    void updateGame() override;
    void unload() override;
};
#endif // !GAME_H