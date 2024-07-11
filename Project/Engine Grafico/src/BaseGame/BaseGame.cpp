#include "../GL/glew.h"
#include "glfw3.h"

#include "BaseGame.h"

#include <random>

namespace Engine {
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

		if (_time != NULL)
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


	bool BaseGame::Initialize(int windowWidth, int windowHeight, const char* windowName)
	{
		if (!glfwInit())
			return false;

		_window = new Window(windowWidth, windowHeight, windowName);

		if (!_window->GetWindow())
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

	void BaseGame::Denitialize()
	{
		glfwTerminate();
	}

	bool BaseGame::WindowExitCheck()
	{
		return glfwWindowShouldClose(_window->GetWindow());
	}

	void BaseGame::InitEngine(int windowWidth, int windowHeight, const char* windowName)
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

	bool BaseGame::IsKeyPressed(int keycode)
	{
		return _input->IsKeyPressed(keycode, _window);
	}

	bool BaseGame::IsKeyDown(int keycode)
	{
		return _input->IsKeyDown(keycode, _window);
	}

	glm::vec2 BaseGame::GetMousePosition()
	{
		return _input->GetMousePosition();
	}

	void BaseGame::ChangeClearColor(glm::vec4 color)
	{
		_renderer->SetColor(color);
	}

	double BaseGame::GetCurrentTime()
	{
		return glfwGetTime();
	}

	float BaseGame::Lerp(float v0, float v1, float t)
	{
		return 0.0f;
	}

	float BaseGame::Lerp(glm::vec4 color1, glm::vec4 color2, float t)
	{
		return 0.0f;
	}

	float BaseGame::GetRandomNumber(float min, float max)
	{
		random_device randDevice; //Using random device since rand() is limited to UINT_MAX
		std::mt19937 mt(randDevice()); //A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits (1)
		std::uniform_real_distribution<float> dist(min, max);
		return dist(mt);
	}

	glm::vec4 BaseGame::GetRandomColor()
	{
		float r = GetRandomNumber(0, 1);
		float g = GetRandomNumber(0, 1);
		float b = GetRandomNumber(0, 1);
		float a = GetRandomNumber(0, 1);

		return glm::vec4(r, g, b, a);
	}

	void BaseGame::AttachCollider(Entity2D* entity, bool isStatic)
	{
		_collisionManager->AddToCollisionList(entity, isStatic);
	}

	void BaseGame::RemoveCollider(Entity2D* entity)
	{
		_collisionManager->RemoveFromCollisionList(entity);
	}

	bool BaseGame::ContainsCollider(Entity2D* entity)
	{
		return _collisionManager->IsInCollisionList(entity);
	}

	void BaseGame::UpdateCollisionsTilemap(Tilemap* tileMap)
	{
		_collisionManager->UpdateCollisions(tileMap);
	}
}

// (1) - Source: https://cplusplus.com/reference/random/mt19937/
// (2) - Source: https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution