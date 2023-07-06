#ifndef LIGHT_H
#define LIGHT_H
#include "../Utils/Export.h"
#include "../Entity/Entity2D.h"
#include "../Shader/Shader.h"
#include "../Renderer/renderer.h"

namespace Engine {
	class ENGINE_API Light : public Entity2D {
	private:
		Shader _shader;
		Renderer* _renderer;
		glm::vec3 _color;
	public:
		Light();
		Light(Renderer* renderer, Shader shader);
		~Light();
		void SetShader(Shader shader);
		void SetRenderer(Renderer* renderer);
		void Init();
		void SetColor(float r, float g, float b);
		void Draw();
	};
}

#endif