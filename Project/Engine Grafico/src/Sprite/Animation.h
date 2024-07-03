#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Utils/Export.h"
#include "glm.hpp"
#include <vector>

namespace Engine {
	
	struct TextureData;

	//Stores configuration of the atlas used for a specific sprite and its details
	class AtlasConfigurations
	{
	public:
		void CutByCount(int columns, int rows, int offsetX, int offsetY, int framesAmount)
		{
			_columns = columns;
			_rows = rows;

			_offsetX = offsetX;
			_offsetY = offsetY;
			_framesAmount = framesAmount;

			_useSize = false;
		}

		void CutBySize(int spriteWidth, int spriteHeight, int offsetX, int offsetY, int framesAmount)
		{
			_spriteWidth = spriteWidth;
			_spriteHeight = spriteHeight;

			_offsetX = offsetX;
			_offsetY = offsetY;
			_framesAmount = framesAmount;

			_useSize = true;
		}

	private:
		int _columns = 1;
		int _rows = 1;

		int _offsetX = 0;
		int _offsetY = 0;
		int _framesAmount = 1;

		bool _useSize = false;

		int _spriteWidth = 0;
		int _spriteHeight = 0;

		friend class Animation;
		friend class Sprite;
	};

	class ENGINE_API Animation
	{
	public:
		Animation();
		~Animation();

		//Standard animation functions
		void Play();
		void Stop();
		bool Update();
		bool IsPlaying();

		//Other animation functions
		void RepeatAnimation(bool active);
		void SetAnimationSpeed(float speed);
		void SetAnimationTimeBetweenFrames(float time);
		void SetAnimationFullTime(float time);
		void SetAnimation(TextureData* animationAtlasData, int columns, int rows);
		void SetAnimation(TextureData* animationAtlasData, AtlasConfigurations config);
		void AddFrameToAnimation(int posX, int posY, int width, int height);
		int GetTextureID();
		glm::vec2* GetCurrentFrameCoordinates();

	private:
		std::vector<glm::vec2*> _frameCoordinates;
		TextureData* _texture;
		int _currentFrame = 0;
		float _currentTime = 0;
		float _timeBetweenFrames = 1.f;
		float _animationSpeed = 1.f;
		bool _repeat = false;
		bool _playing = false;
	};
}

#endif // !ANIMATION_H