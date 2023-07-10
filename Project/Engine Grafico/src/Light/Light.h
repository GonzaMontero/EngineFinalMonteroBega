#ifndef LIGHT_H
#define LIGHT_H
#include "../Utils/Export.h"
#include "../Entity/Entity2D.h"
#include "../Shader/Shader.h"
#include "../Renderer/renderer.h"

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
		glm::vec3 _color;
		LightType _type;
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
		void DrawDirectionalLight();
		void DrawPointLight(int numberOfLight);
	};

	static int _lightCount = 0;
}

#endif