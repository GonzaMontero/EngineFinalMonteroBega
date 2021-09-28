#include "glew.h"
#include "glfw3.h"
#include "BaseGame.h"
#include <stdlib.h>
#include <string>
#include <iostream>

BaseGame::BaseGame() {
	ventana = Window();
	render = Renderer();
}

BaseGame::~BaseGame() {
}


void BaseGame::CloseWindow()
{
	ventana.CloseWindow();
}

void BaseGame::drawTriangle(CVec3 pos1, CVec3 pos2, CVec3 pos3)
{
	render.DrawTriangle(pos1, pos2, pos3);
}

void BaseGame::update()
{

	CVec3 pos1 = { -0.5f, -0.5f, 1, BLUE };
	CVec3 pos2 = { 0.5f, -0.5f, 1, BLUE };
	CVec3 pos3 = { 0.0f, 0.5f, 1, BLUE };
	render.initRender();

	while (!ventana.WindowShouldClose())  //mantiene el bucle mientras que no se cierre la ventana
	{	
		ventana.ClearBackground(); // limbia los buffers

		updateGame();

		render.DrawTriangle(pos1, pos2, pos3);

		ventana.FinishWindowCycle(); // swapea los buffers y ejecuta los eventos
	}
	
	CloseWindow(); // cierra la ventana
}

void BaseGame::initEngine()
{
	ventana.Start(600, 600, "Test2");
}
