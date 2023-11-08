#ifndef NODE_H
#define NODE_H

#include "../Utils/Export.h"
#include "Entity.h"
#include "../Model Importer/Mesh.h"
#include "../Collisions/AABB.h"
#include "../Renderer/renderer.h"
#include "../Shader/Shader.h"
#include "../Material/Material.h"

#include "glm.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace Engine {
	class ENGINE_API Node : public Entity {
	private:
		std::vector<Node*> _children;
		Node* _parent;

		std::vector<Mesh> _meshes;

		std::string _nameNode;

		std::vector<glm::vec3> _aabb;
		std::vector<glm::vec3> _localAABB;
		std::vector<glm::vec3> _aabbPositions;

		AABB* _localBoundingVolume;
		AABB* _volume;

		Renderer* _renderer;
		Shader _shader;

		bool _canDraw;

		Material* _material;

		int _totalNodes;
		int _displayNodes;
		int flag;
		bool yaConto;

		std::vector<Node*> _nodesInCamera;
	public:
		Node();
		~Node();
		void SetChildren(Node* children);
		void SetChildren(std::vector<Node*> children);
		void SetParent(Node* parent);
		void SetMeshes(std::vector<Mesh> meshes);
		void SetLocalBoundingVolume(AABB* localBoundingVolume);
		void SetVolume(AABB* volume);
		void SetName(string name);
		void UpdateNode();
		void UpdateNode(Frustrum& frustum);
		void UpdateNodeChildren();
		std::vector<Node*> GetChildrens();
		Node* GetParent();
		string GetName();
		AABB* GetLocalBoundingVolume();
		AABB* GetVolume();
		void Init(Renderer* renderer);
		void Init(Renderer* renderer, Shader& shader);
		void SetMaterial();
		Node* GetChildrenWithName(string name);
		void GenerateAABB();
		void UpdateAABBchildren(Node* child);
		void Draw(Shader& shader);
		void DrawPlane(Shader& shader);
		void SetCanDraw(bool value);
		bool GetCanDraw();
		void StopDrawNodeAndChildrens(Node* node);
		void BSP(vector<Plane*> planes, Camera* camera);
		void SetMeshPos(float x, float y, float z, int meshIndex);
		void SetMeshScale(float x, float y, float z, int meshIndex);
		void IsOnFrustum(Frustrum& frustum);
	};
}
#endif
