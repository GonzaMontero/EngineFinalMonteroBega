#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H

#include "../Utils/Export.h"
#include "../Model Importer/ModelImp.h"
#include "../Shader/Shader.h"
#include "../Renderer/renderer.h"
#include "../Entity/Node.h"

namespace Engine {
	class ENGINE_API ModelInstance {
	private:
		std::string _path;
		Shader _shader;
		Renderer* _renderer;
		ModelImp* _model;
		Node* _rootNode;
	public:
		ModelInstance(std::string path, Shader& shader, Renderer* renderer);
		~ModelInstance();
		Node* GetRootNode();
		std::vector<Node*> GetPlanesLoaded();
	};
}

#endif
