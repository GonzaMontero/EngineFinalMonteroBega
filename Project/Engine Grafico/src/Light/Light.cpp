#include "light.h"
#include "glew.h"

using namespace Engine;

Light::Light() : Entity2D() {
	_renderer = NULL;
}

Light::Light(Renderer* renderer, Shader shader) : Entity2D() {
	_renderer = renderer;
	_shader = shader;
	_type = LightType::directional;
	_lightCount++;
}

Light::Light(Renderer* renderer, Shader shader, LightType type) : Entity2D() {
	_renderer = renderer;
	_shader = shader;
	_type = type;
	if (_lightCount < 4)
		_lightCount++;
}

Light::~Light() {
	_lightCount--;
}

void Light::SetShader(Shader shader) {
	_shader = shader;
}

void Light::SetRenderer(Renderer* renderer) {
	_renderer = renderer;
}

void Light::Init() {
	if (_type == LightType::directional)
		_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	if (_type == LightType::point) {
		_constant = 1.0f;
		_linear = 0.09f;
		_quadratic = 0.032f;
	}
}


void Light::SetPosition(glm::vec3 position) {
	_position = position;
}

void Light::SetDirection(glm::vec3 direction) {
	_direction = direction;
}

void Light::SetAmbient(glm::vec3 ambient) {
	_ambient = ambient;
}

void Light::SetDiffuse(glm::vec3 diffuse) {
	_diffuse = diffuse;
}

void Light::SetSpecular(glm::vec3 specular) {
	_specular = specular;
}

void Light::SetConstant(float constant) {
	_constant = constant;
}

void Light::SetLinear(float linear) {
	_linear = linear;
}

void Light::SetQuadratic(float quadratic) {
	_quadratic = quadratic;
}

void Light::SetColor(float r, float g, float b) {
	_color = glm::vec3(r, g, b);
	//crear un metodo en la clase shader para setear el color de la variable uniforme lightColor
	//glUniform3f(glGetUniformLocation(_shader.GetID(), "lightColor"), r, g, b);
}

void Light::DrawDirectionalLight() {
	if (_type == LightType::directional)
		_renderer->DrawDirectionalLight(_shader, _position, _color, _direction);
}

void Light::DrawPointLight(int numberOfLight) {
	if (_type == LightType::point) {
		_renderer->DrawPointLight(_shader, _position, _color, _ambient, _diffuse, _specular, _constant, _linear, _quadratic, _lightCount, numberOfLight);
	}
}