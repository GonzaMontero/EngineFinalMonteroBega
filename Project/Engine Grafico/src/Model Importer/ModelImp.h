#ifndef MODELIMP_H
#define MODELIMP_H

#include <glm.hpp>
#include "../stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Shader/Shader.h"
#include "Mesh.h"
#include "../Entity/Entity2D.h"
#include "../Utils/TimeManager.h"
#include "../Camera/Camera.h"
#include "../Entity/Node.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "mat4x4.hpp"

#include "../Utils/TextureImporter.h"

using namespace std;
namespace Engine {
	class ENGINE_API ModelImp {
	private:

		int _width = 0;
		int _height = 0;
		bool _transparency;

		vector<Texture> _textures_loaded;
		//vector<Mesh*> _meshes;
		string _path;

		const char* _modelTexture;
		string _directory;

		//std::vector<Entity2D*> _rootNodeChildren;
		//Entity2D* _rootNode; //Atributo para setear el nodo actual.

		void LoadModel(string path);

		//Each of the following private functions processes a part of the Assimp Import Routine
		void ProcessNode(aiNode* node, const aiScene* scene, Node* parent, glm::mat4 identMatrix);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

		TextureImporter* _texImporter = NULL;
		Shader _shader;
		Renderer* _renderer;

		AABB* _boundingVolume;
		AABB* GenerateGlobalAABB();

		unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
		void LoadTexture();
		unsigned int TextureModel(const char* texture);

		std::vector<Mesh> _meshes;
		std::vector<Node*> _bspPlanes;

		Node* sceneNode;
	public:

		ModelImp();
		ModelImp(string path, const char* modelTexture, Shader& shader, Renderer* renderer);
		ModelImp(string path, Shader& shader, Renderer* renderer);
		~ModelImp();
		
		Mesh* _rootNodeMesh;
		Node* GetSceneNode();
		std::vector<Node*> GetPlanesLoaded();

		void Draw(Shader& shader, Frustrum frustum);
	};
}
#endif
