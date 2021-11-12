#include"glew.h"
#include"glfw3.h"
#include"Sprite.h"


	Sprite::Sprite(bool transparency, Renderer* _renderer) : Entity2D(_renderer) {
		_transparency = transparency;
		_texImporter = new TextureImporter();

	}

	Sprite::Sprite(bool transparency, const char* path, Renderer* _renderer) : Entity2D(_renderer) {
		_transparency = transparency;
		_texImporter = new TextureImporter(path);	
	}

	Sprite::~Sprite() {
		if (_texImporter != NULL) {
			delete _texImporter;
			_texImporter = NULL;
		}
	}

	void Sprite::GenerateVAO() {
		renderer->GenerateVAO(vao);
	}

	void Sprite::BindVAO() {
		renderer->BindVAO(vao);
	}

	void Sprite::BindVBO(float* vertices, int AmmountOfVertices) {
		renderer->BindVBO(vbo, vertices, AmmountOfVertices);
	}

	void Sprite::BindEBO(unsigned int* indices, int AmmountOfVertices) {
		renderer->BindEBO(ebo, indices, AmmountOfVertices);
	}

	void Sprite::Init() {
		renderer->SetTexAttribPointer();
		BindBuffers();
	}

	void Sprite::LoadSprite(int width, int height, const char* path) {
		if (_texImporter) {
			_texImporter->SetPath(path);
			_texImporter->LoadImage(width, height, _transparency);
		}
		else
			std::cout << "Couldn't find image" << std::endl;
	}

	void Sprite::BindBuffers() {
		GenerateVAO();
		BindVAO();
		BindVBO(vertexs, 32);
		BindEBO(indices, 6);
	}

	void Sprite::BindTexture() {
		glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
		glActiveTexture(GL_TEXTURE0);
	}

	void Sprite::BlendSprite() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Sprite::UnBlendSprite() {
		glDisable(GL_BLEND);
	}	

	void Sprite::DrawSprite() {
		UpdateModel();
		if (_transparency) {
			BlendSprite();
			BindTexture();
			renderer->Draw(indices, vertexs, model);
			UnBlendSprite();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			BindTexture();
			renderer->Draw(indices, vertexs, model);
			glDisable(GL_TEXTURE_2D);
		}
	}
	
	void Sprite::SetPath(const char* path) {
		if (_texImporter)
			_texImporter->SetPath(path);
		else
			std::cout << "Couldn't set path" << std::endl;
	}

	const char* Sprite::GetPath() {
		if (_texImporter)
			return _texImporter->GetPath();
		else
			return nullptr;
	}

	void Sprite::UnbindBuffers() {
		renderer->UnbindBuffers();
	}

	void Sprite::DeleteBuffer() {
		renderer->DeleteBuffers(vao, vbo, ebo);
	}


