#ifndef LIGHT_H
#define LIGHT_H

#include "../Utils/Export.h"
#include "../Entity/Entity2D.h"
#include "../Shader/Shader.h"
#include "../Renderer/renderer.h"

/*
Different Lighting Types -

Ambient lighting: even when it is dark there is usually still some light somewhere in the world (the moon, a distant light) so
objects are almost never completely dark. To simulate this we use an ambient lighting constant that always gives the 
object some color.

Diffuse lighting: simulates the directional impact a light object has on an object. This is the most visually significant 
component of the lighting model. The more a part of an object faces the light source, the brighter it becomes.

Specular lighting: simulates the bright spot of a light that appears on shiny objects. Specular highlights are
more inclined to the color of the light than the color of the object.
*/


namespace Engine {
	enum class ENGINE_API LightType {
		directional, point, spot
	};
	class ENGINE_API Light : public Entity2D {
	private:
		Shader _shader;
		Renderer* _renderer;
		glm::vec3 _position;
		glm::vec3 _direction;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
		float _constant;
		float _linear;
		float _quadratic;
		float _cutOff;
		float _outerCutOff;
		glm::vec3 _color;
		LightType _type;
		bool _turnOn;
	public:
		Light();
		Light(Renderer* renderer, Shader shader);
		Light(Renderer* renderer, Shader shader, LightType type);
		~Light();
		void SetShader(Shader shader);
		void SetRenderer(Renderer* renderer);
		void Init();
		void SetPosition(glm::vec3 position);
		void SetDirection(glm::vec3 direction);
		void SetColor(float r, float g, float b);
		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);
		void SetConstant(float constant);
		void SetLinear(float linear);
		void SetQuadratic(float quadratic);
		void SetCutOff(float cutOff);
		void SetOuterCutOff(float outerCutOff);
		void SetTurnOnState(bool state);
		bool GetTurnState();
		void DrawDirectionalLight();
		void DrawPointLight(int numberOfLight);
		void DrawSpotLight();
	};

	static int _lightCount = 0;
}

#endif