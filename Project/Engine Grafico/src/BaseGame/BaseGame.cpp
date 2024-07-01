#include "../GL/glew.h"
#include "glfw3.h"

#include "BaseGame.h"

#include <random>

using namespace Engine;


BaseGame::BaseGame() 
{
	_window = NULL;
	_renderer = NULL;
	_time = NULL;
	_input = NULL;
	_collisionManager = NULL;
}

BaseGame::~BaseGame() 
{
	if (_window != NULL)
	{
		delete _window;
		_window = NULL;
	}

	if (_renderer != NULL) 
	{
		delete _renderer;
		_renderer = NULL;
	}

	if(_time != NULL)
	{
		delete _time;
		_time = NULL;
	}

	if (_input != NULL) 
	{
		delete _input;
		_input = NULL;
	}

	if (_collisionManager != NULL) 
	{
		delete _collisionManager;
		_collisionManager = NULL;
	}
}


bool Engine::BaseGame::Initialize(int windowWidth, int windowHeight, const char* windowName)
{
	if (!glfwInit())
		return false;

	_window = new Window(windowWidth, windowHeight, windowName);

	if (_window->GetWindow())
	{
		glfwTerminate();
		delete _window;
		return false;
	}

	_window->InitWindow();

	if (glewInit() != GLEW_OK) //Check if GLEW Init is successful, checked after GLFW due to being Context Aware
	{
		std::cout << "GLEW Error" << std::endl;
		return false;
	}

	_renderer = new Renderer(_window);

	_time = new Time();

	_input = new Input(_window);

	_collisionManager = new CollisionManager();

	return true;
}

void Engine::BaseGame::Denitialize()
{
	glfwTerminate();
}

bool Engine::BaseGame::WindowExitCheck()
{
	return glfwWindowShouldClose(_window->GetWindow());
}

void Engine::BaseGame::InitEngine(int windowWidth, int windowHeight, const char* windowName)
{
	if (Initialize(windowWidth, windowHeight, windowName)) 
	{
		Init();

		while (!WindowExitCheck())
		{
			glfwPollEvents();

			_time->UpdateDeltaTime(GetCurrentTime());

			Update();

			_renderer->StartDraw();

			Draw();

			_renderer->EndDraw();
		}

		DeInit();

		Denitialize();
	}
}

bool Engine::BaseGame::IsKeyPressed(int keycode)
{
	return _input -> IsKeyPressed(keycode);
}

bool Engine::BaseGame::IsKeyDown(int keycode)
{
	return _input -> IsKeyDown(keycode);
}

glm::vec2 Engine::BaseGame::GetMousePosition()
{
	return _input -> GetMousePosition();
}

void Engine::BaseGame::ChangeClearColor(glm::vec4 color)
{
	_renderer->SetColor(color);
}

double Engine::BaseGame::GetCurrentTime()
{
	return glfwGetTime();
}

float Engine::BaseGame::Lerp(float v0, float v1, float t)
{
	return 0.0f;
}

float Engine::BaseGame::Lerp(glm::vec4 color1, glm::vec4 color2, float t)
{
	return 0.0f;
}

float Engine::BaseGame::GetRandomNumber(float min, float max)
{
	random_device randDevice; //Using random device since rand() is limited to UINT_MAX
	std::mt19937 mt(randDevice()); //A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits (1)
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}

glm::vec4 Engine::BaseGame::GetRandomColor()
{
	float r = GetRandomNumber(0, 1);
	float g = GetRandomNumber(0, 1);
	float b = GetRandomNumber(0, 1);
	float a = GetRandomNumber(0, 1);

	return glm::vec4(r, g, b, a);
}

void Engine::BaseGame::AttachCollider(Entity2D* entity, bool isStatic)
{
	_collisionManager->AddToCollision(entity, isStatic);
}

void Engine::BaseGame::RemoveCollider(Entity2D* entity)
{
	_collisionManager->RemoveFromCollision(entity);
}

bool Engine::BaseGame::ContainsCollider(Entity2D* entity)
{
	return _collisionManager->IsEntityOnCollisions(entity);
}

void Engine::BaseGame::UpdateCollisionsTilemap(Tilemap* tileMap)
{
	_collisionManager->UpdateCollisionsOnMap();
}

//int BaseGame::Init() {
//	_window->CreateWindow("Engine Final Montero-Bega");
//
//	if (!_renderer->InitializeGlew()) 
//	{
//		return 0;
//	}
//
//	basicShader.Create("..//Engine Grafico//src//Shader//shader//vertex.vert", "..//Engine Grafico//src//Shader//shader//fragment.frag");
//	textureShader.Create("..//Engine Grafico//src//Shader//shader//texture_vert.vert", "..//Engine Grafico//src//Shader//shader//texture_frag.frag");
//
//	glEnable(GL_DEPTH_TEST);
//
//	_camera->transform.position = glm::vec3(0.0f, 0.0f, -3.0f);
//
//	_camera->SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//	_camera->SetProjection(ProjectionType::orthographic);
//
//	_camera->Init(basicShader);
//	_camera->Init(textureShader);
//
//
//	input.SetWindow(_window->GetWindow());
//
//	time.Reset();
//
//	InitGame();
//}

// (1) - Source: https://cplusplus.com/reference/random/mt19937/
// (2) - Source: https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution