#ifndef ENTITY_H
#define ENTITY_H

#include "../Utils/Export.h"
#include "../Model Importer/ModelImp.h"
#include "../Shader/Shader.h"
#include "../Renderer/renderer.h"
#include "mat4x4.hpp"
#include "vec3.hpp"

using namespace std;

namespace Engine {
	struct ENGINE_API Trans {
		//Space Information
		//Local space information
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		glm::vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		//Global space information concatenate in matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);
	};

    class ENGINE_API Entity : public ModelImp {
    private:
    public:
        Trans transform;
        Entity() { }
        Entity(string path, Shader& shader, Renderer* renderer) : ModelImp(path, shader, renderer) { }
        //Entity(string path, Shader& shader, Renderer* renderer) : ModelImp(path, shader, renderer) {};
        std::vector<Entity*> children;
        Entity* parent = nullptr;
        //template<typename... TArgs>
        void AddChild(Entity* entity);
        glm::mat4 GetLocalModelMatrix();
        void UpdateSelfAndChild();
    };
}

#endif // !ENTITY_H