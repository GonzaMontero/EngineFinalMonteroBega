#include "Mesh.h"
#include <glew.h>
#include <glfw3.h>

using namespace Engine;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, vector<Mesh*> meshes, Shader& shader, Renderer* renderer) : Entity2D() {
	
	this->vertices = vertices; //Set the public variables as the recieved arguments
	this->indices = indices; //Set the public variables as the recieved arguments
	this->textures = textures; //Set the public variables as the recieved arguments

	_meshes = meshes;

	_shader = shader;

	SetUpMesh();
}

Mesh::~Mesh() {
}

void Mesh::SetUpMesh() {

	_renderer->GenerateVAO(_vao);

	_renderer->BindVAO(_vao);
	_renderer->GenerateVBO(_vbo);

	_renderer->UpdateMeshBuffers(_vbo, vertices.size() * sizeof(Vertex), &vertices[0]);
	_renderer->BindMeshEBO(_ebo, indices.size() * sizeof(unsigned int), &indices[0]);

	_renderer->SetMeshAttribPointers(_shader, 3, sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords));

	glBindVertexArray(0);

	_boundingVolume = GenerateAABB();
}

AABB Mesh::GenerateAABB() {
	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

	for (auto&& mesh : _meshes) {
		for (auto&& vertex : vertices) {
			minAABB.x = std::min(minAABB.x, vertex.Position.x);
			minAABB.y = std::min(minAABB.y, vertex.Position.y);
			minAABB.z = std::min(minAABB.z, vertex.Position.z);

			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
		}
	}
	return AABB(minAABB, maxAABB);
}

void Mesh::Draw(Shader& shader, Frustrum frustrum) {

	//UpdateMatrices();
	UpdateSelfAndChild();
	UpdateVectors();
	//UpdateModel();
	
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++) {

		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
		
		// Retrieve texture number (the N in diffuse_textureN)
		string number; 
		string name = textures[i].type;

		//Locate apropiate Sampler and give it the current active texture before Binding
		if (name == "diffuseM")
			number = std::to_string(diffuseNr++);
		else if (name == "specularM")
			number = std::to_string(specularNr++);
		
		glUniform1f(glGetUniformLocation(shader.GetID(), ("materialPro." + name).c_str()), i);
		
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//Draw Mesh
	if (_boundingVolume.IsOnFrustum(frustum, this))
		_renderer->DrawMesh(shader, _vao, _vbo, vertices.size() * sizeof(Vertex), &vertices[0], indices.size(), sizeof(Vertex), 0, offsetof(Vertex, Normal), offsetof(Vertex, TexCoords), GetModel());
}