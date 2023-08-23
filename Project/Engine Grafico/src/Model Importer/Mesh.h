#ifndef MESH_H
#define MESH_H

#include <glm.hpp>

#include "../Shader/Shader.h"
#include "../Entity/Entity2D.h"
#include "../Renderer/renderer.h"

#include <vector>
#include <string>

#include "../Utils/Export.h"

using namespace std;

namespace Engine {

	//Defining vertex in OpenGL
	struct ENGINE_API Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	//We organize Texture data in this struct
	struct ENGINE_API Texture {
		unsigned int id;
		string type;
		string path;
	};


	/*
	A Mesh can be defined as the minimal representation of a model�s data. It can be seen as pieces of a larger model
	(Example: Gundam Model Parts, they are built separately and joined together later, similar to a model which is composed
	of several different meshes - these could be: head, arms, limbs, etc)
	*/
	class ENGINE_API Mesh : public Entity2D {
	private:
		unsigned int _vao; //Render Data
		unsigned int _vbo; //Render Data
		unsigned int _ebo; //Render Data

		unsigned int _positionAttrib; 
		unsigned int _normalAttrib;
		unsigned int _textureAttrib;

		Shader _shader;
		Renderer* _renderer;

		void SetUpMesh();
	public:
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, 
			Shader &shader, Renderer* renderer); //Constructor
		~Mesh(); //Destructor

		vector<Vertex> vertices; //Mesh Data
		vector<unsigned int> indices; //Mesh Data
		vector<Texture> textures; //Mesh Data

		void Draw(Shader& shader); //We pass shader as a variable so we can set uniforms before drawing
	};
}

#endif