#include "BSPAlgorithm.h"

using namespace Engine;

BSPAlgorithm::BSPAlgorithm() {
	_isSameSign = false;
}

BSPAlgorithm::~BSPAlgorithm() {
	if (!_planes.empty()) {
		for (auto* plane : _planes) {
			if (plane != NULL) {
				delete plane;
				plane = NULL;
			}
		}
		_planes.clear();
	}

	if (!_nodes.empty()) {
		for (auto* model : _nodes) {
			if (model != NULL) {
				delete model;
				model = NULL;
			}
		}
		_nodes.clear();
	}

	if (!_planeModel.empty()) {
		for (auto* planeM : _planeModel) {
			if (planeM != NULL) {
				delete planeM;
				planeM = NULL;
			}
		}
		_planeModel.clear();
	}

	if (_aabb != NULL) {
		delete _aabb;
		_aabb = NULL;
	}
}

void BSPAlgorithm::BSP() {
	for (int i = 0; i < _nodes.size(); i++) {
		CheckBSP(_nodes[i]);
	}
}

void BSPAlgorithm::CheckBSP(Node* node) {
	node->SetCanDraw(true);

	if (node->GetVolume() == NULL && !node->GetChildrens().empty()) {
		for (int i = 0; i < node->GetChildrens().size(); i++) {
			node->UpdateAABBchildren(node->GetChildrens()[i]); //Actualizamos el AABB de los hijos del nodo.
		}
	}

	for (int i = 0; i < _planes.size(); i++) {
		//Si el AABB del nodo no esta del mismo lado que el plano con respecto a la posiciona de la camara, dejo de dibujarlo.
		if (node->GetVolume()->GetGlobalAABBWithMatrix(node->GetModel()).IsOnOrForwardPlan(_planes[i]) != 
			_planes[i]->GetSide(_camera->transform.position)) {
			node->SetCanDraw(false);
			break;
		}
	}

	for (int j = 0; j < node->GetChildrens().size(); j++) {
		CheckBSP(node->GetChildrens()[j]);
	}
}

void BSPAlgorithm::CheckCameraWithPlanes() {
	for (int i = 0; i < _planes.size(); i++) {
		if (!_planes[i]->GetSide(_camera->transform.position))
			_planes[i]->Flip();
	}
}

void BSPAlgorithm::AddPlane(std::vector<Node*> planes) {
	_planeModel = planes;
	for (int i = 0; i < planes.size(); i++) {
		glm::vec3 planeNormal = glm::normalize(_planeModel[i]->GetForwardConst());
		Plane* bspPlane = new Plane(_planeModel[i]->GetPos(), planeNormal);
		_planes.push_back(bspPlane);
	}
}

void BSPAlgorithm::InitPlanes(Renderer* renderer) {
	for (int i = 0; i < _planeModel.size(); i++) {
		_planeModel[i]->Init(renderer);
	}
}

	void BSPAlgorithm::AddNode(Node * node) {
		_nodes.push_back(node);
		if (!node->GetChildrens().empty()) {
			for (int i = 0; i < node->GetChildrens().size(); i++) {
				_nodes.push_back(node->GetChildrens()[i]);
			}
		}

		//Desde el game llamar a AddNode y que el nodo padre se agregue a la lista junto con 
		//sus hijos para hacer el chequeo del BSP.
	}

	void BSPAlgorithm::AddCamera(Camera* camera) {
		_camera = camera;
	}

	void BSPAlgorithm::DrawPlanes(Shader& shader) {
		for (int i = 0; i < _planeModel.size(); i++) {
			_planeModel[i]->DrawPlane(shader);
		}
	}