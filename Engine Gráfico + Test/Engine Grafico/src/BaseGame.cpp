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

	Shape* shapeTest = new Shape(&render);
	shapeTest->Init();

	shapeTest->SetPosition(0.7, 0.5, 0);

	while (!ventana.WindowShouldClose())  //mantiene el bucle mientras que no se cierre la ventana
	{	
		ventana.ClearBackground(); // limbia los buffers

		updateGame();

		shapeTest->Draw();

		ventana.FinishWindowCycle(); // swapea los buffers y ejecuta los eventos
	}
	
	CloseWindow(); // cierra la ventana
}

void BaseGame::initEngine()
{
	ventana.Start(600, 600, "Test2");
}
