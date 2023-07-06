#include "../GL/glew.h"
#include "glfw3.h"

#include "BaseGame.h"

using namespace Engine;

BaseGame::BaseGame() {
	_renderer = new Renderer();
	_window = new Window(1280, 720);
	_camera = new Camera(_renderer, ProjectionType::perspective);
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

void BaseGame::Execute() {
	Init();
	Update();
	Unload();
}

int BaseGame::Init() {
	_window->CreateWindow("Engine Final Montero-Bega");

	if (!_renderer->InitializeGlew()) 
	{
		return 0;
	}

	basicShader.Create("..//Engine Grafico//src//Shader//shader//vertex.vert", "..//Engine Grafico//src//Shader//shader//fragment.frag");
	textureShader.Create("..//Engine Grafico//src//Shader//shader//texture_vert.vert", "..//Engine Grafico//src//Shader//shader//texture_frag.frag");

	glEnable(GL_DEPTH_TEST);

	_camera->transform.position = glm::vec3(0.0f, 0.0f, 3.0f);

	_camera->SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_camera->SetProjection(ProjectionType::perspective);

	_camera->Init(basicShader);
	_camera->Init(textureShader);


	input.SetWindow(_window->GetWindow());

	time.Reset();

	InitGame();
}

void BaseGame::Update() {
	float speed = 0.01f;

	while (!glfwWindowShouldClose(_window->GetWindow())) 
	{
		_renderer->BeginFrame(0.0f, 0.0f, 0.0f);

		UpdateGame();

		_camera->SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		//_camera->Draw(basicShader);
		_camera->Draw(textureShader);

		//int modelLoc = glGetUniformLocation(textureShader.GetID(), "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		time.CalculateFPS();
		time.Tick();

		_renderer->EndFrame(_window->GetWindow());
	}
}

void BaseGame::Unload() {
	UnloadGame();
	glfwTerminate();
}

Renderer* BaseGame::GetRenderer() {
	return _renderer;
}

Window* BaseGame::GetWindow() {
	return _window;
}