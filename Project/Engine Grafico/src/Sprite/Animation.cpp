#include "Animation.h"
#include "../Utils/TextureImporter.h"
#include "../Utils/TimeManager.h"
#include <iostream>

Engine::Animation::Animation()
{
	_texture = nullptr;
}

Engine::Animation::~Animation()
{
	for (unsigned int i = 0; i < _frameCoordinates.size(); i++)
	{
		delete[] _frameCoordinates[i];
	}
}

void Engine::Animation::Play()
{
	_playing = true;
}

void Engine::Animation::Stop()
{
	_playing = false;
}

bool Engine::Animation::Update()
{
	_currentTime += Time::GetDeltaTime() * _animationSpeed;

	if (_currentTime > _timeBetweenFrames)
	{
		_currentTime -= _timeBetweenFrames;
		_currentFrame++;

		if (_currentFrame == _frameCoordinates.size())
		{
			_currentFrame = 0;

			if (_repeat)
				Play();
			else
				Stop();
		}

		return true;
	}

	return false;
}

bool Engine::Animation::IsPlaying()
{
	return _playing;
}

void Engine::Animation::RepeatAnimation(bool active)
{
	_repeat = active;
}

void Engine::Animation::SetAnimationSpeed(float speed)
{
	_animationSpeed = speed;
}

void Engine::Animation::SetAnimationTimeBetweenFrames(float time)
{
	_timeBetweenFrames = time;
}

void Engine::Animation::SetAnimationFullTime(float time)
{
	_animationSpeed = 1;
	_timeBetweenFrames = time / _frameCoordinates.size();
}

void Engine::Animation::SetAnimation(TextureData* animationAtlasData, int columns, int rows)
{
	_texture = animationAtlasData;

	float spriteWidth = _texture->width / columns;
	float spriteHeight = _texture->height / rows;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			glm::vec2* newCoord = new glm::vec2[4];

			newCoord[0].x = (spriteWidth + (spriteWidth * j)) / _texture->width;			// top right
			newCoord[0].y = (spriteHeight * i) / _texture->height;						// top right

			newCoord[1].x = (spriteWidth + (spriteWidth * j)) / _texture->width; 		// bottom right
			newCoord[1].y = (spriteHeight + (spriteHeight * i)) / _texture->height;		// bottom right

			newCoord[2].x = (spriteWidth * j) / _texture->width;							// bottom left
			newCoord[2].y = (spriteHeight + (spriteHeight * i)) / _texture->height;		// bottom left

			newCoord[3].x = (spriteWidth * j) / _texture->width;							// top left 
			newCoord[3].y = (spriteHeight * i) / _texture->height;						// top left 

			_frameCoordinates.push_back(newCoord);
		}
	}
}

void Engine::Animation::SetAnimation(TextureData* animationAtlasData, AtlasConfigurations config)
{
	_texture = animationAtlasData;

	int spriteWidth = 0;
	int spriteHeight = 0;

	if (config._useSize)
	{
		spriteWidth = config._spriteWidth;
		spriteHeight = config._spriteHeight;
	}
	else
	{
		spriteWidth = (int)(_texture->width / config._columns);
		spriteHeight = (int)(_texture->height / config._rows);
	}

	int framesCount = 0;
	int x = config._offsetX;

	for (int i = config._offsetX; i < config._rows; i++)
	{
		while (x < config._columns)
		{
			glm::vec2* newCoord = new glm::vec2[4];

			newCoord[0].x = (spriteWidth + (spriteWidth * x)) / _texture->width;
			newCoord[0].y = spriteHeight * i / _texture->height;

			newCoord[1].x = (spriteWidth + (spriteWidth * x)) / _texture->width;
			newCoord[1].y = (spriteHeight + (spriteHeight * i)) / _texture->height;

			newCoord[2].x = (spriteWidth * x) / _texture->width;
			newCoord[2].y = (spriteHeight + (spriteHeight * i)) / _texture->height;

			newCoord[3].x = (spriteWidth * x) / _texture->width;
			newCoord[3].y = (spriteHeight * i) / _texture->height;

			_frameCoordinates.push_back(newCoord);
			framesCount++;
			x++;

			if (framesCount == config._framesAmount)
				return;
		}
		x = 0;
	}
}

void Engine::Animation::AddFrameToAnimation(int posX, int posY, int width, int height)
{
	glm::vec2* newCoord = new glm::vec2[4];

	newCoord[0].x = (width + (width * posX)) / _texture->width;			// top right
	newCoord[0].y = (height * posY) / _texture->height;						// top right

	newCoord[1].x = (width + (width * posX)) / _texture->width; 			// bottom right
	newCoord[1].y = (height + (height * posY)) / _texture->height;		// bottom right

	newCoord[2].x = (width * posX) / _texture->width;							// bottom left
	newCoord[2].y = (height + (height * posY)) / _texture->height;		// bottom left

	newCoord[3].x = (width * posX) / _texture->width;							// top left 
	newCoord[3].y = (height * posY) / _texture->height;						// top left 

	_frameCoordinates.push_back(newCoord);
}

glm::vec2* Engine::Animation::GetCurrentFrameCoordinates()
{
	return _frameCoordinates[_currentFrame];
}
