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
		LoadSprite(_width, _height, path);

		cout << "width: " << _width << endl;
		cout << "height: " << _height << endl;
	}

	Sprite::Sprite(): Entity2D()
	{
		_transparency = false;
		renderer = nullptr;
	}

	Sprite::~Sprite() {
		if (_texImporter != NULL) {
			delete _texImporter;
			_texImporter = NULL;
		}
	}

	void Sprite::setAnimation(Animation* animation)
	{
		anim = animation;
		_previousFrame = std::numeric_limits<unsigned int>::max_digits10;
	}

	Animation* Sprite::getAnimation()
	{
		return anim;
	}

	void Sprite::setAnimCoords(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3)
	{		
		vertexs[6] = u0;   vertexs[7] = v0;
		vertexs[14] = u1;  vertexs[15] = v1;
		vertexs[22] = u2;  vertexs[23] = v2;
		vertexs[30] = u3;  vertexs[31] = v3;
	}

	void Sprite::updateAnimation(Time& time)
	{
		if (anim != NULL) {
			anim->update(time);
			_currentFrame = anim->getCurrentFrame();

			if (_currentFrame != _previousFrame) {
				setAnimCoords(anim->getAnimation()[_currentFrame].frameCoordinates[0].u, anim->getAnimation()[_currentFrame].frameCoordinates[0].v,
					anim->getAnimation()[_currentFrame].frameCoordinates[3].u, anim->getAnimation()[_currentFrame].frameCoordinates[3].v,
					anim->getAnimation()[_currentFrame].frameCoordinates[2].u, anim->getAnimation()[_currentFrame].frameCoordinates[2].v,
					anim->getAnimation()[_currentFrame].frameCoordinates[1].u, anim->getAnimation()[_currentFrame].frameCoordinates[1].v);
				_previousFrame = _currentFrame;
			}
			setAnimation(anim);
		}

	}

	void Sprite::blendSprite()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Sprite::unblendSprite()
	{
		glDisable(GL_BLEND);
	}

	void Sprite::SetCurrentAnimationIndex(int currentAnimation)
	{
		if (anim != NULL) anim->setCurrentAnimation(currentAnimation);
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
		glEnable(GL_TEXTURE_2D);
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
		glActiveTexture(GL_TEXTURE0); ///sacar?
		UpdateModel();
		if (_transparency) {
			BlendSprite();
			BindTexture();
			renderer->DrawSprite(vao, vbo, vertexs,32, model, indices);
			UnBlendSprite();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			BindTexture();
			renderer->DrawSprite(vao, vbo, vertexs, 32, model, indices);
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


