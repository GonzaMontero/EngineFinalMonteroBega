#include "../GL/glew.h"
#include "glfw3.h"

#include "BaseGame.h"

using namespace Engine;

BaseGame::BaseGame() {
	_renderer = new Renderer();
	_window = new Window(1280, 720);
	_camera = new Camera(_renderer, ProjectionType::orthographic);
	_collisionManager = new CollisionManager();
}

BaseGame::~BaseGame() {
	if (_renderer != NULL) {
		delete _renderer;
		_renderer = NULL;
	}

	if (_window != NULL)
	{
		delete _window;
		_window = NULL;
	}

	if (_camera != NULL) {
		delete _camera;
		_camera = NULL;
	}

	if (_collisionManager != NULL) {
		delete _collisionManager;
		_collisionManager = NULL;
	}
}

void BaseGame::Execute() { //Inicia todo desde main
	Init();
	Update();
	Unload();
}

int BaseGame::Init() {
	// Inicia las cosas necesarias para correr el motor, ventana, glew, shaders, camera, view, resetea el timer, inicia el game, etc...
	_window->CreateWindow("Engine Final Montero-Bega");

	if (!_renderer->InitializeGlew()) 
	{
		return 0;
	}

	basicShader.Create("..//Engine Grafico//src//Shader//shader//vertex.vert", "..//Engine Grafico//src//Shader//shader//fragment.frag");
	textureShader.Create("..//Engine Grafico//src//Shader//shader//texture_vert.vert", "..//Engine Grafico//src//Shader//shader//texture_frag.frag");

	glEnable(GL_DEPTH_TEST);

	_camera->transform.position = glm::vec3(0.0f, 0.0f, -3.0f);

	_camera->SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_camera->SetProjection(ProjectionType::orthographic);

	_camera->Init(basicShader);
	_camera->Init(textureShader);


	input.SetWindow(_window->GetWindow());

	time.Reset();

	InitGame();
}

void BaseGame::Update() {
	//Updatea el timer, revisa si no hay que cerrar la vantana del motor, actualiza game, dibuja lo que ve la camara con los shaders
	float speed = 0.01f;

	while (!glfwWindowShouldClose(_window->GetWindow())) 
	{
		_renderer->BeginFrame(0.0f, 0.0f, 0.0f);

		UpdateGame();

		_camera->Draw(basicShader);
		_camera->Draw(textureShader);

		time.CalculateFPS();
		time.Tick();

		_renderer->EndFrame(_window->GetWindow());
	}
}

void BaseGame::Unload() {
	//Destruye las cosas para liberar el espacio en memoria
	UnloadGame();
	glfwTerminate();
}

Renderer* BaseGame::GetRenderer() {
	return _renderer;
}

Window* BaseGame::GetWindow() {
	return _window;
}