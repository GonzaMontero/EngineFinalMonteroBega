#include "Game.h"

using namespace Engine;

float speed = 10.0f;

glm::vec3 direction = glm::vec3(0.0f);
glm::vec3 scale = glm::vec3(0.0f);
glm::vec3 rot = glm::vec3(0.0f);

glm::vec3 pointLightPositions[4] = {
		glm::vec3(0.0f, 0.0f, -2.0f),
		glm::vec3(5.0f, 0.0f, -2.0f),
		glm::vec3(10.0f, 0.0f, -2.0f),
		glm::vec3(15.0f, 0.05f, -2.0f)
};

float rotationSpeed = 100.0f;

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

	if (_model != NULL) {
		delete _model;
		_model = NULL;
	}

	if (_spotLight != NULL) {
		delete _spotLight;
		_spotLight = NULL;
	}
}

void Game::InitGame() {

	_sprite = new Sprite(true, "res/textures/container2.png", "res/textures/container2_specular.png", GetRenderer(), basicShader, MaterialType::lambertPro);

	_shape = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::gold);
	_shape2 = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::esmerald);

	_dirLight = new Light(GetRenderer(), basicShader, LightType::directional);
	_spotLight = new Light(GetRenderer(), basicShader, LightType::spot);

	for (int i = 0; i < 4; i++) {
		_light[i] = new Light(GetRenderer(), basicShader, LightType::point);
		_light[i]->SetPosition(pointLightPositions[i]);
	}

	_model = new ModelImp("res/models/bar/source/Bar_stool.fbx", basicShader);
	_model->Scale(2.0f, 2.0f, 2.0f);
	_model->Translate(0.0f, 0.0f, 0.0f);

	_model->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	_model->transform.scale = glm::vec3(10.0f);

	_shape->Init();
	_shape2->Init();

	_sprite->Init();

	_dirLight->Init();
	_dirLight->SetColor(1.0f, 1.0f, 0.0f);

	_spotLight->Init();
	_spotLight->transform.position = glm::vec3(0.0f, 0.0f, -2.0f);

	_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	_shape->transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);

	_shape2->Color(0.0f, 0.0f, 1.0f);
	_shape2->transform.position = glm::vec3(-12.0f, 0.0f, -10.0f);
	_shape2->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);

	_shape->RotateX(1.0f * speed * time.GetDeltaTime());

	_sprite->transform.position = glm::vec3(15.0f, 0.0f, -10.0f);
	_sprite->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);
}

void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::I)) {
		//_camera->transform.position.z -= speed * time.GetDeltaTime();
		_spotLight->transform.position.x -= speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::O)) {
		_spotLight->transform.position.x += speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::P)) {
		_light[0]->SetTurnOnState(false);
		_spotLight->SetTurnOnState(false);
		_dirLight->SetTurnOnState(false);
	}

	else if (input.GetKey(KeyCode::L)) {
		_light[0]->SetTurnOnState(true);
		_spotLight->SetTurnOnState(true);
		_dirLight->SetTurnOnState(true);
	}

	else if (input.GetKey(KeyCode::W)) {
		_camera->transform.position += speed * time.GetDeltaTime() * _camera->GetCameraFront();
	}

	else if (input.GetKey(KeyCode::S)) {
		_camera->transform.position -= speed * time.GetDeltaTime() * _camera->GetCameraFront();
	}

	else if (input.GetKey(KeyCode::A)) {
		_camera->transform.position -= glm::normalize(glm::cross(_camera->GetCameraFront(), _camera->GetCameraUp())) * speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::D)) {
		_camera->transform.position += glm::normalize(glm::cross(_camera->GetCameraFront(), _camera->GetCameraUp())) * speed * time.GetDeltaTime();

	}

	else if (input.GetKey(KeyCode::H)) {
		scale.x += speed * time.GetDeltaTime();
		scale.y += speed * time.GetDeltaTime();
		scale.z += speed * time.GetDeltaTime();
		_model->ScaleModel(scale.x, scale.y, scale.z);
	}

	else if (input.GetKey(KeyCode::G)) {
		direction.x += speed * time.GetDeltaTime();
		_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::X)) {
		rot.x += speed * time.GetDeltaTime();
		_model->RotateModelX(rot.x);
	}

	else if (input.GetKey(KeyCode::Y)) {
		rot.y += speed * time.GetDeltaTime();
		_model->RotateModelY(rot.y);
	}

	else if (input.GetKey(KeyCode::Z)) {
		rot.z += speed * time.GetDeltaTime();
		_model->RotateModelZ(rot.z);
	}

	else if (input.GetKey(KeyCode::F)) {
		_spotLight->transform.position.z += speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::V)) {
		_spotLight->transform.position.z -= speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::F)) {
		direction.x -= speed * time.GetDeltaTime();
		_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::T)) {
		direction.y += speed * time.GetDeltaTime();
		_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::C)) {
		direction.y -= speed * time.GetDeltaTime();
		_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}

	else if (input.GetKey(KeyCode::J)) {
		scale.x -= speed * time.GetDeltaTime();
		scale.y -= speed * time.GetDeltaTime();
		scale.z -= speed * time.GetDeltaTime();
		_model->ScaleModel(scale.x, scale.y, scale.z);
	}

	if (input.GetKey(KeyCode::DOWN)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotatePitch(-rotationSpeed * time.GetDeltaTime());
	}

	if (input.GetKey(KeyCode::UP)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotatePitch(rotationSpeed * time.GetDeltaTime());
	}

	if (input.GetKey(KeyCode::LEFT)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotateYaw(-rotationSpeed * time.GetDeltaTime());
	}

	if (input.GetKey(KeyCode::RIGHT)) {
		//_camera->_rotationSpeed = rotationSpeed * time.GetDeltaTime();
		_camera->RotateYaw(rotationSpeed * time.GetDeltaTime());
	}
}

void Game::UpdateGame() {

	PlayerInputs();

	_camera->FollowTarget(_model->transform.position);

	_camera->UpdateRotation();
	_camera->SetLookAt(_camera->GetCameraFront());
	_camera->Draw(basicShader);

	_shape->Draw();
	_shape2->Draw();

	_model->Draw(basicShader);

	_dirLight->DrawDirectionalLight();
	_spotLight->DrawSpotLight();

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

	if (_spotLight != NULL) {
		delete _spotLight;
		_spotLight = NULL;
	}

	if (_model != NULL) {
		delete _model;
		_model = NULL;
	}
}