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

namespace Engine {

	class Window;
	class Renderer;
	class Input;
	class CollisionManager;

	class ENGINE_API BaseGame {
	private:
		//Internal functions to initialize all elements
		bool Initialize(int windowWidth, int windowHeight, const char* windowName);
		void Denitialize();
		bool WindowExitCheck();

		//Internal elements (not to be accessed by the end user)
		Window* _window;
		Input* _input;
		Time* _time;
		CollisionManager* _collisionManager;

	protected:
		Renderer* _renderer;

	public:
		BaseGame();
		~BaseGame();

		//External Functions which can be used by the end user
		void InitEngine(int windowWidth, int windowHeight, const char* windowName);

		//Virtual functions which will allow the end user to override them and add code to be executed - I.E. adding draw calls 
		//for Sprites
		virtual void Init() = 0; //Initial function which will not only enable and create engine classes but also initialize end user
									//classes
		virtual void Update() = 0; //Updates all frames and is used by end user for movement, as an example
		virtual void Draw() = 0; //Sends data for drawing all on screen elements, and the end user manually adds all foreign elements
		virtual void DeInit() = 0; //Allows the end user to unload all data used during runtime

		//Useful methods for the end user to perform - Input
		bool IsKeyPressed(int keycode); //Pressed = Will return true every frame the key is pressed
		bool IsKeyDown(int keycode); //Down = Will return true the first frame the key is pressed ONLY
		glm::vec2 GetMousePosition(); //Returns the mouse position on screen

		//Useful methods for the end user to perform - Config and Time
		void ChangeClearColor(glm::vec4 color); //Swaps the color used during the screen clear to specified values
		double GetCurrentTime(); //Returns time elapsed since GLFW initialized

		//Useful methods for the end user to perform - Calculations and Random
		float Lerp(float v0, float v1, float t); //Interpolates between two values based on T
		float Lerp(glm::vec4 color1, glm::vec4 color2, float t); //Interpolates between two colors based on T
		float GetRandomNumber(float min, float max); //Returns a random number between the min and max value parameters
		glm::vec4 GetRandomColor(); //Returns a random color

		//Useful methods for the end user to perform - Collision Calculations and Modifications
		void AttachCollider(Entity2D* entity, bool isStatic); //Attaches a collider to a specific entity and if movement is possible
		void RemoveCollider(Entity2D* entity); //Removes collider from specific entity, if possible
		bool ContainsCollider(Entity2D* entity); //Checks if specified entity contains a collider
		void UpdateCollisionsTilemap(Tilemap* tileMap); // Checks collisions on the specified tilemap
	};
}
#endif // !BASEGAME_H