#include "Game.h"

float speed = 10.0f;
float rotSpeed = 200.0f;
float movementSpeed = 20.0f;

using namespace std;
using namespace Engine;

glm::vec3 pointLightPositions[4] = {
		glm::vec3(-12.0f, 0.0f, -2.0f),
		glm::vec3(5.0f, 0.0f, -2.0f),
		glm::vec3(10.0f, 0.0f, -2.0f),
		glm::vec3(15.0f, 0.05f, -2.0f)
};

float rotationSpeed = 100.0f;
glm::vec3 direction = glm::vec3(0.0f);
glm::vec3 scale = glm::vec3(0.0f);
glm::vec3 rot = glm::vec3(0.0f);

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
	if (_dirLight != NULL) {
		delete _dirLight;
		_dirLight = NULL;
	}
	if (_spotLight != NULL) {
		delete _spotLight;
		_spotLight = NULL;
	}
	if (_modelLeft != NULL) {
		delete _modelLeft;
		_modelLeft = NULL;
	}

	if (_modelRight != NULL) {
		delete _modelRight;
		_modelRight = NULL;
	}

	if (_modelForward != NULL) {
		delete _modelForward;
		_modelForward = NULL;
	}

	if (_modelMobile != NULL) {
		delete _modelMobile;
		_modelMobile = NULL;
	}

	for (int i = 0; i < 3; i++) {
		if (_bspPlanes[i] != NULL) {
			delete _bspPlanes[i];
			_bspPlanes[i] = NULL;
		}
	}

	if (_bsp != NULL) {
		delete _bsp;
		_bsp = NULL;
	}
}

void Game::InitGame() {	
#pragma region INIT
	_sprite = new Sprite(true, "res/textures/container2.png", "res/textures/container2_specular.png", GetRenderer(), basicShader, MaterialType::lambertPro);
	
	_shape = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::gold);
	_shape2 = new Shape(Type::cube, GetRenderer(), basicShader, MaterialType::esmerald);
	_sprite = new Sprite(true, "res/textures/container2.png", "res/textures/container2_specular.png", GetRenderer(), basicShader, MaterialType::lambertPro);

	_dirLight = new Light(GetRenderer(), basicShader, LightType::directional);

	_spotLight = new Light(GetRenderer(), basicShader, LightType::spot);
	
	for (int i = 0; i < 4; i++) {
		_light[i] = new Light(GetRenderer(), basicShader, LightType::point);
		_light[i]->Init();
		_light[i]->SetPosition(pointLightPositions[i]);
	}

	
	string modelpath = "res/models/scene2/scene-planes.fbx";
	_model = new ModelInstance(modelpath, basicShader, GetRenderer());

	_modelLeft = _model->GetRootNode()->GetChildrenWithName("Left");
	_modelLeft->Init(GetRenderer(), basicShader);
	_modelRight = _model->GetRootNode()->GetChildrenWithName("Right");
	_modelRight->Init(GetRenderer(), basicShader);
	_modelForward = _model->GetRootNode()->GetChildrenWithName("Forward");
	_modelForward->Init(GetRenderer(), basicShader);
	_modelMobile = _model->GetRootNode()->GetChildrenWithName("Mobile");
	_modelMobile->Init(GetRenderer(), basicShader);
	
	_shape->Init();
	_shape2->Init();
	_sprite->Init();

	//_model->SetParent(_shape);
	
	_dirLight->Init();
	
	_dirLight->SetColor(1.0f, 1.0f, 0.0f);
	_spotLight->Init();
	_spotLight->transform.position = glm::vec3(0.0f, 0.0f, -2.0f);
	
	_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0.0f, 0.0f, -20.0f);
	_shape->transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);

	_shape2->Color(0.0f, 0.0f, 1.0f);
	_shape2->transform.position = glm::vec3(-12.0f, 0.0f, -20.0f);
	_shape2->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);
	
	_sprite->transform.position = glm::vec3(15.0f, 0.0f, -20.0f);
	_sprite->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);

	//BSP
	_bsp = new BSPAlgorithm();
	_bsp->AddNode(_modelMobile);
	_bsp->AddNode(_modelLeft);
	_bsp->AddNode(_modelRight);
	_bsp->AddNode(_modelForward);

	//Agregar camara al BSP
	_bsp->AddCamera(_camera);

	//Agregar planos
	std::cout << "Get planes loaded: " << _model->GetPlanesLoaded().size() << std::endl;
	_bsp->AddPlane(_model->GetPlanesLoaded());

	_bsp->InitPlanes(GetRenderer());

#pragma endregion
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
	else if (input.GetKey(KeyCode::B)) {
		_spotLight->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::V)) {
		_spotLight->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::L)) {
		_light[0]->SetTurnOnState(true);
		_spotLight->SetTurnOnState(true);
		_dirLight->SetTurnOnState(true);
	}
	else if (input.GetKey(KeyCode::G)) {
		direction.x += speed * time.GetDeltaTime();
		_modelMobile->SetPos(direction.x, direction.y, direction.z);
		//_bspPlanes[0]->setPos(_bspPlanes[0]->getPos(_bspPlanes[0]->getModel() + direction.x));
		//_model->MoveModel(direction);
		//_modelA->Translate(direction.x, direction.y, direction.z);
		//std::cout << "_modelA X " << _modelA->transform.position.x << std::endl;
		//std::cout << "_bspPlanes 0 X " << _bspPlanes[0]->transform.position.x << std::endl;
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::F)) {
		direction.x -= speed * time.GetDeltaTime();
		//_bspPlanes[1]->setPos(direction.x, direction.y, direction.z);
		_modelMobile->SetPos(direction.x, direction.y, direction.z);
		//_modelLeft->setPos(direction);
		//_bspPlanes[1]->setPos(_bspPlanes[1]->getPos(_bspPlanes[1]->getModel() + direction.x));
		//_model->MoveModel(direction);
		//_shape->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::T)) {
		direction.y += movementSpeed * time.GetDeltaTime();
		_modelMobile->SetPos(direction.x, direction.y, direction.z);
		//_bspPlanes[2]->Translate(direction.x, direction.y, direction.z);
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::C)) {
		direction.y -= movementSpeed * time.GetDeltaTime();
		_modelMobile->SetPos(direction.x, direction.y, direction.z);
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::K)) {
		direction.z -= movementSpeed * time.GetDeltaTime();
		_modelMobile->SetPos(direction.x, direction.y, direction.z);
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::R)) {
		direction.z += movementSpeed * time.GetDeltaTime();
		_modelMobile->SetPos(direction.x, direction.y, direction.z);
		//_model->MoveModel(direction);
		//_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::H)) {
		scale.x += speed * time.GetDeltaTime();
		scale.y += speed * time.GetDeltaTime();
		scale.z += speed * time.GetDeltaTime();
		//_shape->Scale(scale.x, scale.y, scale.z);
		//_model->ScaleModel(scale.x, scale.y, scale.z);
	}
	else if (input.GetKey(KeyCode::J)) {
		scale.x -= speed * time.GetDeltaTime();
		scale.y -= speed * time.GetDeltaTime();
		scale.z -= speed * time.GetDeltaTime();
		//_shape->Scale(scale.x, scale.y, scale.z);
		//_model->ScaleModel(scale.x, scale.y, scale.z);
	}

	else if (input.GetKey(KeyCode::N)) {
		scale.x += speed * time.GetDeltaTime();
		scale.y += speed * time.GetDeltaTime();
		scale.z += speed * time.GetDeltaTime();
		_shape->Scale(scale.x, scale.y, scale.z);
		//_model->ScaleModel(scale.x, scale.y, scale.z);
	}
	else if (input.GetKey(KeyCode::M)) {
		scale.x -= speed * time.GetDeltaTime();
		scale.y -= speed * time.GetDeltaTime();
		scale.z -= speed * time.GetDeltaTime();
		_shape->Scale(scale.x, scale.y, scale.z);
		//_model->ScaleModel(scale.x, scale.y, scale.z);
	}
	else if (input.GetKey(KeyCode::X)) {
		//_planes[0].SetNormal(glm::vec3(-0.100f, 0.23f, 0.96f));
		//_planes[0].SetNormal(glm::vec3(0.0f, 0.0f, -1.0f));
		rot.x += rotSpeed * time.GetDeltaTime();
		//_modelA->RotateModelX(rot.x);
		_modelMobile->SetRot(rot.x, rot.y, rot.z);
	}
	else if (input.GetKey(KeyCode::Y)) {
		rot.y += rotSpeed * time.GetDeltaTime();
		//_modelA->RotateModelY(rot.y);
		//_model->RotateModelY(rot.y);
		_modelMobile->SetRot(rot.x, rot.y, rot.z);
	}
	else if (input.GetKey(KeyCode::Z)) {
		//_planes[0].SetNormal(glm::vec3(0.57f, 0.0f, 0.81f));
		//_planes[0].SetNormal(glm::vec3(0.0f, 0.0f, 1.0f));
		rot.z += rotSpeed * time.GetDeltaTime();
		//_modelA->RotateModelZ(rot.z);
		//_model->RotateModelZ(rot.z);
		_modelMobile->SetRot(rot.x, rot.y, rot.z);
	}
	else if (input.GetKey(KeyCode::A)) {
		_camera->transform.position.x -= speed * time.GetDeltaTime();
		//_shape->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::LEFT)) {
		_light[0]->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::RIGHT)) {
		_light[0]->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::UP)) {
		_light[0]->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::DOWN)) {
		_light[0]->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::T)) {
		float value = 10.0f;
		value += 20.0f * time.GetDeltaTime();
		_shape2->RotateZ(value);
	}

	if (input.GetKey(KeyCode::W)) {
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

	camFrustum = _camera->CreateFrustumFromCamera(1280.0f / 720.0f, glm::radians(43.0f), 0.1f, 100.0f);

	_modelLeft->UpdateNode(camFrustum);
	_modelRight->UpdateNode(camFrustum);
	_modelForward->UpdateNode(camFrustum);
	_modelMobile->UpdateNode(camFrustum);

	_camera->UpdateRotation();
	_camera->SetLookAt(_camera->GetCameraFront());

	_bsp->CheckCameraWithPlanes();
	_bsp->BSP();

	_camera->Draw(basicShader);

	_shape->Draw();
	_shape2->Draw();
	
	_dirLight->DrawDirectionalLight();
	_spotLight->DrawSpotLight();

	for (int i = 0; i < 4; i++)
		_light[i]->DrawPointLight(i);

	_sprite->DrawSprite();

	_bsp->DrawPlanes(basicShader);
}

void Game::UnloadGame() {
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

	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
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
	if (_bsp != NULL) {
		delete _bsp;
		_bsp = NULL;
	}
}