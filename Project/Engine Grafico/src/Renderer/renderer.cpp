#include "glew.h"
#include "glfw3.h"

#include "Renderer.h"
#include "../Shader/Shader.h"

#include <iostream>
#include "string"

using namespace Engine;

Renderer::Renderer() {
}
Renderer::~Renderer() {
}
bool Renderer::InitializeGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in GLEW INIT" << std::endl;
		std::cout << glewGetErrorString(glewInit()) << std::endl;
		return false;
	}
	return true;
}
void Renderer::BeginFrame(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::EndFrame(GLFWwindow* window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Renderer::GenerateVAO(unsigned int& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}
void Renderer::BindVAO(unsigned int& vao) {
	glBindVertexArray(vao);
}
void Renderer::GenerateLightVAO(unsigned int& lightvao) {
	glGenVertexArrays(1, &lightvao);
	glBindVertexArray(lightvao);
}
void Renderer::BindLightVAO(unsigned int& lightvao) {
	glBindVertexArray(lightvao);
}
void Renderer::BindBufferLight(unsigned int& vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
void Renderer::GenerateVBO(unsigned int& vbo) {
	glGenBuffers(1, &vbo);
}
void Renderer::BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::BindLightVBO(unsigned int& lightvbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &lightvbo);
	glBindBuffer(GL_ARRAY_BUFFER, lightvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
void Renderer::BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}
void Renderer::BindMeshEBO(unsigned int& ebo, int indicesAmount, const void* data) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesAmount, data, GL_STATIC_DRAW);
}
void Engine::Renderer::UpdateBuffers(unsigned int& vbo, float* vertices, int verticesAmmount) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::UpdateMeshBuffers(unsigned int& vbo, int verticesAmount, const void* data) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesAmount, data, GL_STATIC_DRAW);
}
void Renderer::UnbindBuffers() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, unsigned int& lightvao) {
	glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &lightvao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
void Renderer::CreateAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition) {
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE, sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}
void Renderer::SetShader(Shader& shader) {
	_shader = shader;
}
Shader& Renderer::GetShader() {
	return _shader;
}
void Renderer::SetMeshAttribPointers(Shader& shader, unsigned int dataAmount, unsigned int vertexSize, unsigned int posOffset, unsigned int normalOffset, unsigned int textureOffset) {
	unsigned int posAttribute = glGetAttribLocation(shader.GetID(), "position");
	glVertexAttribPointer(posAttribute, dataAmount, GL_FLOAT, GL_FALSE, vertexSize, (void*)posOffset);
	glEnableVertexAttribArray(posAttribute);
	unsigned int normalAttribue = glGetAttribLocation(shader.GetID(), "aNormal");
	glVertexAttribPointer(normalAttribue, dataAmount, GL_FLOAT, GL_FALSE, vertexSize, (void*)normalOffset);
	glEnableVertexAttribArray(normalAttribue);
	unsigned int textureAttribute = glGetAttribLocation(shader.GetID(), "uv");
	glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)textureOffset);
	glEnableVertexAttribArray(textureAttribute);
}

void Renderer::Draw(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount, Material* material) {
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);
	shader.SetVertexAttributes("position", 11); //especificamos como leer los datos del vertice y se lo pasamos al shader
	shader.SetColorAttributes("color", 11);
	//Crear en la clase shader un metodo para leer los nuevos datos de normales
	shader.SetNormalAttributes("aNormal", 11); //ya esta
	shader.SetTypeOfshape("type", 0);
	//Le pasamos al shder la matriz modelo de cada shape
	shader.Use(model);
	//Aplicamos el material de cada shape respectivamente
	//El material se va a setear en el constructor de cada shape
	material->ApplyMaterial(shader);
	//Aca le estamos seteando la posicion de la luz al uniforme del fragment shader, cuando este la clase light lista pasarlo para ahi.
	glDrawElements(GL_TRIANGLES, indicesAmmount, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

void Renderer::DrawPointLight(Shader& shader, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, int cantOfLights, int numberOfLight) {
	shader.Use();

	std::string uniformPointLightPosition = "pointLight[" + std::to_string(numberOfLight) + "].position";
	std::string uniformPointLightAmbient = "pointLight[" + std::to_string(numberOfLight) + "].ambient";
	std::string uniformPointLightDiffuse = "pointLight[" + std::to_string(numberOfLight) + "].diffuse";
	std::string uniformPointLightSpecular = "pointLight[" + std::to_string(numberOfLight) + "].specular";
	std::string uniformPointLightConstant = "pointLight[" + std::to_string(numberOfLight) + "].constant";
	std::string uniformPointLightLinear = "pointLight[" + std::to_string(numberOfLight) + "].linear";
	std::string uniformPointLightQuadratic = "pointLight[" + std::to_string(numberOfLight) + "].quadratic";

	unsigned int pointLightPositionLoc = glGetUniformLocation(shader.GetID(), uniformPointLightPosition.c_str());
	glUniform3fv(pointLightPositionLoc, 1, glm::value_ptr(lightPos));
	unsigned int pointLightAmbientLoc = glGetUniformLocation(shader.GetID(), uniformPointLightAmbient.c_str());
	glUniform3fv(pointLightAmbientLoc, 1, glm::value_ptr(ambient));
	unsigned int pointLightDiffuseLoc = glGetUniformLocation(shader.GetID(), uniformPointLightDiffuse.c_str());
	glUniform3fv(pointLightDiffuseLoc, 1, glm::value_ptr(diffuse));
	unsigned int pointLightSpecularLoc = glGetUniformLocation(shader.GetID(), uniformPointLightSpecular.c_str());
	glUniform3fv(pointLightSpecularLoc, 1, glm::value_ptr(specular));

	unsigned int pointLightConstantLoc = glGetUniformLocation(shader.GetID(), uniformPointLightConstant.c_str());
	glUniform1f(pointLightConstantLoc, constant);
	unsigned int pointLightLinearLoc = glGetUniformLocation(shader.GetID(), uniformPointLightLinear.c_str());
	glUniform1f(pointLightLinearLoc, linear);
	unsigned int pointLightQuadraticLoc = glGetUniformLocation(shader.GetID(), uniformPointLightQuadratic.c_str());
	glUniform1f(pointLightQuadraticLoc, quadratic);
}

void Renderer::DrawDirectionalLight(Shader& shader, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	shader.Use();
	
	unsigned int lightColorLoc = glGetUniformLocation(shader.GetID(), "lightColor");
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
	unsigned int lightAmbientLoc = glGetUniformLocation(shader.GetID(), "dirLight.ambient");
	glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(ambient));
	unsigned int lightDiffuseLoc = glGetUniformLocation(shader.GetID(), "dirLight.diffuse");
	glUniform3fv(lightDiffuseLoc, 1, glm::value_ptr(diffuse));
	unsigned int lightSpecularLoc = glGetUniformLocation(shader.GetID(), "dirLight.specular");
	glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(specular));
	
	unsigned int lightDirectionLoc = glGetUniformLocation(shader.GetID(), "dirLight.direction");
	glUniform3fv(lightDirectionLoc, 1, glm::value_ptr(direction));
}

void Renderer::DrawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount, glm::mat4 model, Material* material) {
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);
	shader.SetVertexAttributes("position", 11);
	shader.SetColorAttributes("color", 11);
	shader.SetNormalAttributes("aNormal", 11);
	shader.SetTextureAttributes("uv", 11);
	shader.SetTypeOfshape("type", 1);
	shader.Use(model);
	material->ApplyMaterial(shader);
	glDrawElements(GL_TRIANGLES, indicesAmmount, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

void Renderer::DrawSpotLight(Shader& shader, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff) {
	shader.Use();
	unsigned int lightPosLocation = glGetUniformLocation(shader.GetID(), "spotLight.position");
	glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));
	unsigned int lightDirLocation = glGetUniformLocation(shader.GetID(), "spotLight.direction");
	glUniform3fv(lightDirLocation, 1, glm::value_ptr(lightDir));
	unsigned int lightAmbientLocation = glGetUniformLocation(shader.GetID(), "spotLight.ambient");
	glUniform3fv(lightAmbientLocation, 1, glm::value_ptr(ambient));
	unsigned int lightDiffuseLocation = glGetUniformLocation(shader.GetID(), "spotLight.diffuse");
	glUniform3fv(lightDiffuseLocation, 1, glm::value_ptr(diffuse));
	unsigned int lightSpecularLocation = glGetUniformLocation(shader.GetID(), "spotLight.specular");
	glUniform3fv(lightSpecularLocation, 1, glm::value_ptr(specular));
	unsigned int lightConstantLocation = glGetUniformLocation(shader.GetID(), "spotLight.constant");
	glUniform1f(lightConstantLocation, constant);
	unsigned int lightLinearLocation = glGetUniformLocation(shader.GetID(), "spotLight.linear");
	glUniform1f(lightLinearLocation, linear);
	unsigned int lightQuadraticLocation = glGetUniformLocation(shader.GetID(), "spotLight.quadratic");
	glUniform1f(lightQuadraticLocation, quadratic);
	unsigned int lightCutOffLocation = glGetUniformLocation(shader.GetID(), "spotLight.cutOff");
	glUniform1f(lightCutOffLocation, cutOff);
	unsigned int lightOuterCutOff = glGetUniformLocation(shader.GetID(), "spotLight.outerCutOff");
	glUniform1f(lightOuterCutOff, outerCutOff);
}

void Renderer::DrawLightCube(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount) {
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);

	shader.SetVertexAttributes("position", 9);

	shader.SetNormalAttributes("aNormal", 9);

	shader.Use(model);

	glUniform3f(glGetUniformLocation(shader.GetID(), "objectColor"), 1.0f, 1.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, indicesAmmount, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

void Renderer::DrawMesh(Shader& shader, unsigned int& vao, unsigned int& vbo, int verticesAmount, const void* dataVertices, int indicesAmmount, unsigned int vertexSize, unsigned int offsetOfVertex, unsigned int offsetOfNormal, unsigned int offsetOfTexture, glm::mat4 model) {
	BindVAO(vao);
	UpdateMeshBuffers(vbo, verticesAmount, dataVertices);
	shader.Use(model);
	shader.SetTypeOfshape("type", 2);
	shader.SetMeshAttribPointers("position", 3, vertexSize, offsetOfVertex);
	shader.SetMeshAttribPointers("aNormal", 3, vertexSize, offsetOfNormal);
	shader.SetMeshAttribPointers("uv", 2, vertexSize, offsetOfTexture);
	//attrib pointers si hace falta
	//BindVAO(vao);
	glDrawElements(GL_TRIANGLES, indicesAmmount, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}
void Renderer::DrawCamera(Shader& shader, glm::vec3 camPos, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	//unsigned int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
	unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");
	unsigned int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
	//Pasamos la posicion de la camara para calcular la iluminacion specular
	unsigned int camPosLoc = glGetUniformLocation(shader.GetID(), "viewPos");
	shader.Use(model);
	glUniform3fv(camPosLoc, 1, glm::value_ptr(camPos));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}