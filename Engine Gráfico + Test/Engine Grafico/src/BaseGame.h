#ifndef BASEGAME_H
#define BASEGAME_H

#include "Export.h"

#include "Window.h"
#include "renderer.h"

#include "Global.h"

class ENGINE_API BaseGame {
public:
	BaseGame();
	~BaseGame();
	Window ventana;
	Renderer render;
	void CloseWindow();
	void drawTriangle(CVec3 pos1, CVec3 pos2, CVec3 pos3);
	void update();
	void initEngine();
	virtual void init() = 0;
	virtual void updateGame() = 0;
	virtual void unload() = 0;
};
#endif // !BASEGAME_H