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

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "../Utils/TextureImporter.h"

using namespace std;
namespace Engine {
	class ENGINE_API ModelImp : public Entity2D {

	private:

		int _width = 0;
		int _height = 0;
		bool _transparency;

		//Model Data (textures, meshes and file path)
		vector<Texture> _textures_loaded;
		vector<Mesh*> _meshes;
		string _path;

		const char* _modelTexture;
		string _directory;

		std::vector<Entity2D*> _rootNodeChildren;
		Entity2D* _rootNode;

		void LoadModel(string path);

		//Each of the following private functions processes a part of the Assimp Import Routine
		void ProcessNode(aiNode* node, const aiScene* scene, Entity2D* parent);
		Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

		TextureImporter* _texImporter = NULL;
		Shader _shader;
		Renderer* _renderer;

		AABB* _boundingVolume;
		AABB* GenerateGlobalAABB();

		unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
		void LoadTexture();
		unsigned int TextureModel(const char* texture);
	public:

		ModelImp();
		ModelImp(string path, const char* modelTexture, Shader& shader, Renderer* renderer);
		ModelImp(string path, Shader& shader, Renderer* renderer);
		~ModelImp();

		void MoveModel(glm::vec3 direction);

		void ScaleModel(float x, float y, float z);
		void RotateModelX(float x);
		void RotateModelY(float y);
		void RotateModelZ(float z);

		void Draw(Shader& shader, Frustrum frustum);
	};
}
#endif
