#include"glew.h"
#include"glfw3.h"
#include"Sprite.h"
#include "../Sprite/Animation.h"
#include "../Renderer/renderer.h"
#include "../Utils/TextureImporter.h"
#include "../Utils/TimeManager.h"

namespace Engine {

	Sprite::Sprite() 
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = nullptr;

		uvCoords[0] = { 1.0f, 1.0f };
		uvCoords[1] = { 1.0f, 0.0f };
		uvCoords[2] = { 0.0f, 0.0f };
		uvCoords[3] = { 0.0f, 1.0f };
	}

	Sprite::Sprite(Renderer* renderer, const char* imagePath, bool invertImage)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = renderer;

		uvCoords[0] = { 1.0f, 1.0f };
		uvCoords[1] = { 1.0f, 0.0f };
		uvCoords[2] = { 0.0f, 0.0f };
		uvCoords[3] = { 0.0f, 1.0f };

		SetTexture(renderer, imagePath, invertImage);
	}

	Sprite::~Sprite() 
	{

	}

	void Sprite::Draw()
	{
		_renderer->textureShader.Use();
		unsigned int texture = GetCurrentTextureID();
		glBindTexture(GL_TEXTURE_2D, texture);
		SetShader(texture);
		_renderer->Draw(_model.trs, VAO, _vertices, _renderer->textureShader.GetID());
	}

	void Sprite::ModifyTextureCoords(AtlasConfigurations config)
	{
		int spriteWidth;
		int spriteHeight;
		
		if (config._useSize)
		{
			spriteWidth = config._spriteWidth;
			spriteHeight = config._spriteHeight;
		}
		else
		{
			spriteWidth = (int)(_baseTexture->width / config._columns);
			spriteHeight = (int)(_baseTexture->height / config._rows);
		}

		uvCoords[0].x = (spriteWidth + (spriteWidth * config._offsetX)) / _baseTexture->width;		// top right
		uvCoords[0].y = (spriteHeight * config._offsetY) / _baseTexture->height;						// top right
		uvCoords[1].x = (spriteWidth + (spriteWidth * config._offsetX)) / _baseTexture->width; 		// bottom right
		uvCoords[1].y = (spriteHeight + (spriteHeight * config._offsetY)) / _baseTexture->height;		// bottom right
		uvCoords[2].x = (spriteWidth * config._offsetX) / _baseTexture->width;						// bottom left
		uvCoords[2].y = (spriteHeight + (spriteHeight * config._offsetY)) / _baseTexture->height;		// bottom left
		uvCoords[3].x = (spriteWidth * config._offsetX) / _baseTexture->width;						// top left 
		uvCoords[3].y = (spriteHeight * config._offsetY) / _baseTexture->height;						// top left

		float UVs[8]
		{
			uvCoords[0].x,uvCoords[0].y,
			uvCoords[1].x,uvCoords[1].y,
			uvCoords[2].x,uvCoords[2].y,
			uvCoords[3].x,uvCoords[3].y
		};

		_renderer->BindBufferAdditional(_bufferPosUV, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	}

	TextureData* Sprite::CreateAnimationData(const char* AtlasFilePath, bool invertImage)
	{
		return new TextureData(TextureImporter::LoadTexture(AtlasFilePath,invertImage));
	}

	void Sprite::DeleteAnimationData(TextureData* atlasToDelete)
	{
		delete atlasToDelete;
	}

	int Sprite::CreateAnimation()
	{
		Animation* anim = new Animation();
		_allAnimations.push_back(anim);
		return _allAnimations.size() - 1;
	}

	int Sprite::CreateAnimation(AtlasConfigurations config)
	{
		Animation* anim = new Animation();
		anim->SetAnimation(_baseTexture, config);
		_allAnimations.push_back(anim);
		return _allAnimations.size() - 1;
	}

	int Sprite::CreateAnimation(TextureData* animationData, int columns, int rows)
	{
		Animation* anim = new Animation();
		anim->SetAnimation(animationData, columns, rows);
		_allAnimations.push_back(anim);
		return _allAnimations.size() - 1;
	}

	int Sprite::CreateAnimation(TextureData* animationData, AtlasConfigurations config)
	{
		Animation* anim = new Animation();
		anim->SetAnimation(animationData, config);
		_allAnimations.push_back(anim);
		return _allAnimations.size() - 1;
	}

	void Sprite::AddFrameToExistingAnimation(int animationID, int positonX, int positionY, int width, int height)
	{
		_allAnimations[animationID]->AddFrameToAnimation(positonX, positionY, width, height);
	}

	void Sprite::PlayAnimation(int ID)
	{
		if (!_allAnimations[ID]->IsPlaying())
		{
			for (unsigned int i = 0; i < _allAnimations.size(); i++)
				_allAnimations[i]->Stop();

			_allAnimations[ID]->Play();
		}
	}

	void Sprite::StopAnimation(int ID)
	{
		_allAnimations[ID]->Stop();
	}

	void Sprite::SetAnimationRepeat(int ID, bool active)
	{
		_allAnimations[ID]->RepeatAnimation(active);
	}

	void Sprite::StopAllAnimations()
	{
		for (unsigned int i = 0; i < _allAnimations.size(); i++)
			_allAnimations[i]->Stop();
	}

	void Sprite::SetAnimationSpeed(int ID, float speed)
	{
		_allAnimations[ID]->SetAnimationSpeed(speed);
	}

	void Sprite::SetAnimationTimeBetweenFrames(int ID, float time)
	{
		_allAnimations[ID]->SetAnimationTimeBetweenFrames(time);
	}

	void Sprite::SetAnimationFullTime(int ID, float time)
	{
		_allAnimations[ID]->SetAnimationFullTime(time);
	}

	void Sprite::SetTextureCoordinates(glm::vec2 coord1, glm::vec2 coord2, glm::vec2 coord3, glm::vec2 coord4)
	{
		uvCoords[0].x = coord1.x;
		uvCoords[0].y = coord1.y;

		uvCoords[1].x = coord2.x;
		uvCoords[1].y = coord2.y;

		uvCoords[2].x = coord3.x;
		uvCoords[2].y = coord3.y;

		uvCoords[3].x = coord4.x;
		uvCoords[3].y = coord4.y;
	}

	void Sprite::SetTexture(Renderer* renderer, const char* filePathImage, bool invertImage)
	{
		_renderer = renderer;

		float vertex[24] =
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};

		_renderer->CreateBufferInitial(VAO, VBO, EBO);
		_renderer->BindBufferInitial(VAO, VBO, EBO, vertex, sizeof(vertex), indices, sizeof(indices));
		_vertices = 6;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		float UVs[8] =
		{
			uvCoords[0].x, uvCoords[0].y,
			uvCoords[1].x, uvCoords[1].y,
			uvCoords[2].x, uvCoords[2].y,
			uvCoords[3].x, uvCoords[3].y
		};

		_renderer->CreateBufferAdditional(_bufferPosUV, 1);
		_renderer->BindBufferAdditional(_bufferPosUV, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);

		_baseTexture = new TextureData(TextureImporter::LoadTexture(filePathImage, invertImage));
	}

	void Sprite::Denitialize()
	{
		_renderer->DeleteBufferInitial(VAO, VBO, EBO);
		_renderer->DeleteBufferAdditional(_bufferPosUV, 1);
		glDeleteTextures(1, &_baseTexture->ID);

		delete _baseTexture;

		for (unsigned int i = 0; i < _allAnimations.size(); i++)
		{
			delete _allAnimations[i];
		}
	}

	void Sprite::SetShader(unsigned int texture)
	{
		glm::vec3 newColor = glm::vec3(_color.r, _color.g, _color.b);

		unsigned int colorLoc = glGetUniformLocation(_renderer->textureShader.GetID(), "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(_renderer->textureShader.GetID(), "a");
		glUniform1fv(alphaLoc, 1, &(_color.a));

		unsigned int textureLoc = glGetUniformLocation(_renderer->textureShader.GetID(), "ourTexture");
		glUniform1f(textureLoc, (GLfloat)texture);
	}

	unsigned int Sprite::GetCurrentTextureID()
	{
		for (unsigned int i = 0; i < _allAnimations.size(); i++)
		{
			if (_allAnimations[i]->IsPlaying())
			{
				if (_allAnimations[i]->Update())
				{
					BindUVCoords(i);
					_lastCoordIndex = i;
				}
				return _allAnimations[i]->GetTextureID();
			}
		}

		if (_allAnimations.size() > 0)
			BindUVCoords(_lastCoordIndex);
		else
			BindUVCoords();

		return _baseTexture->ID;
	}

	void Sprite::BindUVCoords()
	{
		float UVs[8] =
		{
			uvCoords[0].x, uvCoords[0].y,
			uvCoords[1].x, uvCoords[1].y,
			uvCoords[2].x, uvCoords[2].y,
			uvCoords[3].x, uvCoords[3].y
		};

		_renderer->BindBufferAdditional(_bufferPosUV, UVs, sizeof(UVs), GL_STATIC_DRAW);
	}

	void Sprite::BindUVCoords(int i)
	{
		glm::vec2* uv = _allAnimations[i]->GetCurrentFrameCoordinates();

		float UVs[8] =
		{
			uv[0].x, uv[0].y,
			uv[1].x, uv[1].y,
			uv[2].x, uv[2].y,
			uv[3].x, uv[3].y
		};

		_renderer->BindBufferAdditional(_bufferPosUV, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	}
}