#ifndef BASEGAME_H
#define BASEGAME_H

#include "../Utils/Export.h"

#include "../Renderer/renderer.h"
#include "../Window/Window.h"
#include "../Shader/Shader.h"
#include "../Shape/Shape.h"
#include "../Sprite/Sprite.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Sprite/Animation.h"
#include "../Utils/TimeManager.h"
#include "../Collision/Collision Manager.h"
#include "../Tilemap/Tile.h"
#include "../Tilemap/Tilemap.h"
#include "../xml_lib/tinyxml2.h"
#include "../Light/Light.h"

namespace Engine {
	class ENGINE_API BaseGame {
	private:
		Renderer* _renderer;
		Window* _window;

	protected:
		//void mouse_callback(GLFWwindow* window, double posX, double posY);

		Camera* _camera;
		Shader basicShader;
		//Shader textureShader;
		//Shader lightShader;
		Renderer* GetRenderer();
		Window* GetWindow();
		CollisionManager* _collisionManager;

		Time time;
		Input input;

		int Init();
		void Update();
		void Unload();

	public:
		BaseGame();
		~BaseGame();

		void Execute();

		virtual void InitGame() = 0;
		virtual void UpdateGame() = 0;
		virtual void UnloadGame() = 0;	
	};
}
#endif // !BASEGAME_H