#ifndef BASEGAME_H
#define BASEGAME_H

#include "Export.h"

#include "Window.h"
#include "renderer.h"
#include "Shape.h"

#include "Global.h"

class ENGINE_API BaseGame {
public:
	BaseGame();
	~BaseGame();
	Window ventana;
	Renderer render;
	void CloseWindow();
	void update();
	void initEngine();
	virtual void init() = 0;
	virtual void updateGame() = 0;
	virtual void unload() = 0;
};
#endif // !BASEGAME_H