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

void BaseGame::update()
{
	render.initRender();

	while (!ventana.WindowShouldClose())  //mantiene el bucle mientras que no se cierre la ventana
	{	
		ventana.ClearBackground(); // limbia los buffers

		updateGame();


		ventana.FinishWindowCycle(); // swapea los buffers y ejecuta los eventos
	}
	
	CloseWindow(); // cierra la ventana
}

void BaseGame::initEngine()
{
	ventana.Start(600, 600, "Test2");
}

void BaseGame::draw(shapes shape)
{

	Shape* shapeTest = new Shape(&render);
	shapeTest->Init();

	switch (shape)
	{
	case BaseGame::TRIANGLE:
		shapeTest->Draw();
		break;
	case BaseGame::SQUARE:
		shapeTest->Draw();
		break;
	default:
		break;
	}
}
