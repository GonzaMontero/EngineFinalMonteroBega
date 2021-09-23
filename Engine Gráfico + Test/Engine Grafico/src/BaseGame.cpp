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

int BaseGame::StartWindow(int width, int height, const char* windowName)
{
	return ventana.Start(width, height, windowName);
}

void BaseGame::CloseWindow()
{
	ventana.CloseWindow();
}

void BaseGame::drawTriangle(CVec4 pos1, CVec4 pos2, CVec4 pos3)
{
	render.DrawTriangle(pos1, pos2, pos3);
}

void BaseGame::update()
{
	//initGame; (Virtual)
	CVec4 pos1 = { -0.5f, -0.5f, 1, 1, BLUE };
	CVec4 pos2 = { 0.5f, -0.5f, 1, 1, BLUE };
	CVec4 pos3 = { 0.0f, 0.5f, 1, 1, BLUE };

	while (!ventana.WindowShouldClose())  //mantiene el bucle mientras que no se cierre la ventana
	{	
		ventana.ClearBackground(); // limbia los buffers

		updateGame();

		render.DrawTriangle(pos1, pos2, pos3);

		ventana.FinishWindowCycle(); // swapea los buffers y ejecuta los eventos
	}

	//deInitGame; (Virtual)
	CloseWindow(); // cierra la ventana
}