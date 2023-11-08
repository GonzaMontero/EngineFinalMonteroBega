#ifndef BSP_ALGORITHM_H
#define BSP_ALGORITHM_H

#include "../Utils/Export.h"
#include "../Model Importer/Mesh.h"
#include "../Model Importer/ModelImp.h"
#include "../Plane/Plane.h"
#include "../Camera/Camera.h"
#include "../Entity/Node.h"
#include "../Renderer/renderer.h"
#include "../Shader/Shader.h"
#include "AABB.h"

#include "glm.hpp"

#include <vector>
#include <iostream>

using namespace std;

namespace Engine {
	class ENGINE_API BSPAlgorithm {
	private:
		bool _isSameSign; //test
		std::vector<Plane*> _planes;
		std::vector<Node*> _planeModel;
		std::vector<Node*> _nodes;
		Camera* _camera;
		AABB* _aabb;
	public:
		BSPAlgorithm();
		~BSPAlgorithm();
		void BSP();
		void CheckCameraWithPlanes();
		void CheckBSP(Node* node);
		//void CheckPlaneWithCamera(Camera* camera);
		void AddPlane(std::vector<Node*> planes);
		void InitPlanes(Renderer* renderer);
		void AddNode(Node* model);
		void AddCamera(Camera* camera);
		void DrawPlanes(Shader& shader);
	};
}

#endif
