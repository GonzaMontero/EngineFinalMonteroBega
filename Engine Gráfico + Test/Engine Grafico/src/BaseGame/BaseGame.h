#ifndef BASEGAME_H
#define BASEGAME_H

#include "../Utils/Export.h"

#include "../Window/Window.h"
#include "../Renderer/renderer.h"
#include "../Shape/Shape.h"
#include "../Sprite/Sprite.h"
#include "../Input/Input.h"
#include "../Collision/Collision Manager.h"
#include "../Sprite/Animation.h"
#include "../Tilemap/Tilemap.h"


namespace Engine {
	class ENGINE_API BaseGame {
	private:
		Renderer* _renderer;
		Window* _window;
	protected:
		Camera* _camera;
		Shader basicShader;
		Shader textureShader;
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