#ifndef NODE_H
#define NODE_H

#include "../Utils/Export.h"
#include "Entity.h"
#include "../Model Importer/Mesh.h"
#include "../Collisions/AABB.h"
#include "../Renderer/renderer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"

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
		void SetTransformMatrix();
		std::vector<Node*> GetChildrens();
		Node* GetParent();
		string GetName();
		AABB* GetLocalBoundingVolume();
		AABB* GetVolume();
		void SetRenderer(Renderer* renderer);
		Node* GetChildrenWithName(string name);
		void GenerateAABB();
		void UpdateAABBchildren(Node* child);
		void Draw(Shader& shader, Frustrum& frustum);
	};
}

#endif
