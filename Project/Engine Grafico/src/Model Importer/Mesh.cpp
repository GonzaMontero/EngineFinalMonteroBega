#include "Mesh.h"
#include <glew.h>
#include <glfw3.h>

using namespace Engine;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Shader& shader, Renderer* renderer) : Entity2D() {

	this->vertices = vertices;

	this->indices = indices;

	this->textures = textures;
}

Mesh::~Mesh() {

}

void Mesh::SetUpMesh() {

	_renderer->GenerateVAO(_vao);
	_renderer->BindVAO(_vao);

	_renderer->BindMeshEBO(_ebo, indices.size() * sizeof(unsigned int), &indices[0]);

	_renderer->SetMeshAttribPointers(_shader, 3, sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader) {
	UpdateMatrices();
	UpdateModel();
	//Pasar este codigo a renderer y que reciba como parametros todos los datos necesarios
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string name = textures[i].type;
		if (name == "diffuseM")
			number = std::to_string(diffuseNr++);
		else if (name == "specularM")
			number = std::to_string(specularNr++);
	
		glUniform1f(glGetUniformLocation(shader.GetID(), ("materialPro." + name).c_str()), i);

		glBindTexture(GL_TEXTURE_2D, textures[i].id);

	}

	_renderer->DrawMesh(shader, _vao, _vbo, vertices.size() * sizeof(Vertex), &vertices[0], indices.size(), sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords), GetModel());
}