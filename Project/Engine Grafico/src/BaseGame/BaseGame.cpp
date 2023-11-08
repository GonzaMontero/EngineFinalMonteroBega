#include "../GL/glew.h"
#include "glfw3.h"

#include "BaseGame.h"

using namespace Engine;

BaseGame::BaseGame() {
	_renderer = new Renderer();
	_window = new Window(1280, 720);
	_camera = new Camera(_renderer, ProjectionType::perspective, CamMode::thirdPerson);
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

	if (_modelMobile != NULL) {
		delete _modelMobile;
		_modelMobile = NULL;
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
	stbi_set_flip_vertically_on_load(true);
	//_renderer->SetShader(basicShader);

	glEnable(GL_DEPTH_TEST);

	_camera->transform.position = glm::vec3(0.0f, 0.0f, 3.0f);

	_camera->SetProjection(ProjectionType::perspective);
	_camera->Init(basicShader, _window->GetWindow());

	_camera->SetCameraUp(glm::vec3(0.0, 1.0, 0.0));

	input.SetWindow(_window->GetWindow());

	time.Reset();

	InitGame();

#pragma region Init
	_modelMobile->GetChildrens()[4]->SetMeshPos(0.0f, 0.0f, 1.0f, 0); //Cabeza
	_modelMobile->GetChildrens()[4]->SetMeshScale(3.0f, 1.0f, 3.0f, 0);
	_modelMobile->GetChildrens()[1]->SetMeshPos(0.0f, 0.0f, -2.5f, 0); //Cadera
	_modelMobile->GetChildrens()[3]->SetMeshPos(0.0f, 0.0f, -1.0f, 0); //Torzo

	_modelMobile->GetChildrens()[3]->SetMeshScale(0.3f, 0.4f, 1.0f, 0);
	_modelMobile->GetChildrens()[5]->SetMeshPos(0.0f, -1.4f, -1.0f, 0); //Brazo izquiedo
	_modelMobile->GetChildrens()[5]->SetMeshScale(0.6f, 1.9f, 0.6f, 0);
	_modelMobile->GetChildrens()[2]->SetMeshPos(0.0f, 1.5f, -1.0f, 0); //Brazo derecho

	_modelMobile->GetChildrens()[0]->SetMeshPos(0.0f, 3.0f, -1.0f, 0); //Mano derecha
	_modelMobile->GetChildrens()[6]->SetMeshPos(0.0f, -3.0f, -1.0f, 0); //Mano izquierda
	_modelMobile->GetChildrens()[6]->SetMeshScale(1.01f, 1.0f, 0.85f, 0);

	_modelMobile->GetChildrens()[8]->SetMeshPos(0.0f, 0.7f, -3.7f, 0); //Pie derecho
	_modelMobile->GetChildrens()[8]->SetMeshScale(0.5f, 0.5f, 1.20f, 0);
	_modelMobile->GetChildrens()[7]->SetMeshPos(0.0f, -0.7f, -3.7f, 0); //Pie izquierdo
	_modelMobile->GetChildrens()[7]->SetMeshScale(0.5f, 0.5f, 1.0f, 0);
	
	_modelMobile->SetRotRadians(glm::vec3(270.0f, 0.0f, 0.0f));
#pragma endregion
}

void BaseGame::Update() {
	float speed = 50.0f;
	float rotationSpeed = 50.0f;

	while (!glfwWindowShouldClose(_window->GetWindow())) 
	{
		_renderer->BeginFrame(0.0f, 0.0f, 0.0f);

		UpdateGame();

		if (_modelMobile->GetChildrens()[0]->GetCanDraw()) {
			_modelMobile->GetChildrens()[2]->SetCanDraw(true);
			_modelMobile->GetChildrens()[3]->SetCanDraw(true);
		}
		else if (_modelMobile->GetChildrens()[6]->GetCanDraw()) {
			_modelMobile->GetChildrens()[5]->SetCanDraw(true);
			_modelMobile->GetChildrens()[3]->SetCanDraw(true);
		}
		
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