#include "Game.h"

float speed = 100.f;

glm::vec3 pointLightPositions[4] = {
		glm::vec3(0.0f, 0.0f, -2.0f),
		glm::vec3(5.0f, 0.0f, -2.0f),
		glm::vec3(10.0f, 0.0f, -2.0f),
		glm::vec3(15.0f, 0.05f, -2.0f)
};

Game::Game() {

}

Game::~Game() {

	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}

	for (int i = 0; i < 4; i++) {
		if (_light[i] != NULL) {
			delete _light[i];
			_light[i] = NULL;
		}
	}
}

void Game::InitGame() {

	_sprite = new Sprite(true, "res/textures/container2.png", "res/textures/container2_specular.png", GetRenderer(), basicShader, MaterialType::lambertPro);

	_shape = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::gold);
	_shape2 = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::esmerald);

	_dirLight = new Light(GetRenderer(), basicShader, LightType::directional);

	for (int i = 0; i < 4; i++) {
		_light[i] = new Light(GetRenderer(), basicShader, LightType::point);
		_light[i]->SetPosition(pointLightPositions[i]);
		_light[i]->SetAmbient(glm::vec3(0.2f));
		_light[i]->SetDiffuse(glm::vec3(0.5f));
		_light[i]->SetSpecular(glm::vec3(1.0f));
		_light[i]->SetConstant(1.0f);
		_light[i]->SetLinear(0.09f);
		_light[i]->SetQuadratic(0.032f);
	}

	//_light[3]->transform.position = pointLightPositions[3];
	//
	//for (int i = 0; i < 3; i++) {
	//	_light[i]->transform.position = pointLightPositions[i];
	//}

	_shape->Init();
	_shape2->Init();

	_sprite->Init();

	//Crear un array de posiciones para las luces y array de ambient, diffuse, specular, eviar hardcodeo.

	_dirLight->Init();

	_dirLight->SetColor(1.0f, 1.0f, 0.0f);

	_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	_shape->transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);

	_shape2->Color(0.0f, 0.0f, 1.0f);
	_shape2->transform.position = glm::vec3(2.0f, 0.0f, -10.0f);
	_shape2->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);

	_shape->RotateX(1.0f * speed * time.GetDeltaTime());

	_sprite->transform.position = glm::vec3(15.0f, 0.0f, -10.0f);
	_sprite->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);
}

void Game::PlayerInputs() {

	if (input.GetKey(KeyCode::W)) {
		_shape->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::S)) {
		_shape->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::D)) {
		_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::A)) {
		_shape->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::T)) {
		float value = 10.0f;
		value += 20.0f * time.GetDeltaTime();
		_shape2->RotateZ(value);
	}
}

void Game::UpdateGame() {

	PlayerInputs();

	_camera->FollowTarget(_shape->transform.position);

	_shape->Draw();
	_shape2->Draw();

	_dirLight->DrawDirectionalLight();

	for (int i = 0; i < 4; i++)
		_light[i]->DrawPointLight(i);

	_sprite->DrawSprite();
}

void Game::UnloadGame() {

	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}

	for (int i = 0; i < 4; i++) {
		if (_light[i] != NULL) {
			delete _light[i];
			_light[i] = NULL;
		}
	}

	if (_dirLight != NULL) {
		delete _dirLight;
		_dirLight = NULL;
	}
}