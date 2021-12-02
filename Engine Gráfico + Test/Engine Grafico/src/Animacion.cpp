#include "animation.h"
#include <iostream>

Animation::Animation()
{
	_currentTime = 0;
	_currentFrame = 0;
	_length = 0;
}

Animation::~Animation() {}

void Animation::update(Time& timer)
{
	_currentTime = (timer.GetTime() * _length);

	while (_currentTime >= _length) {
		_currentTime -= _length;
	}
	float frameLength = _length / _animations[_currentAnimation].size();
	_currentFrame = static_cast<int>(_currentTime / frameLength);
}
void Animation::addFrame(float frameX, float frameY, int spriteWidth, int spriteHeigth, int textureWidth, int textureHeigth, float timeToAnim, int totalFrames, int counColumnas)
{
	int miliseconds = 1000;
	_length = timeToAnim * miliseconds;

	float index_X = 0;
	float index_Y = 0;
	Frame frame;
	for (int i = 0; i < totalFrames; i++) {
		//--------
		frame.frameCoordinates[0].u = ((frameX + index_X) / textureWidth);
		frame.frameCoordinates[0].v = ((spriteHeigth + index_Y) / textureHeigth);

		frame.frameCoordinates[1].u = (((frameX + index_X) + spriteWidth) / textureWidth);
		frame.frameCoordinates[1].v = ((spriteHeigth + index_Y) / textureHeigth);

		frame.frameCoordinates[2].u = (((frameX + index_X) + spriteWidth) / textureWidth);
		frame.frameCoordinates[2].v = ((frameY + index_Y) / textureHeigth);

		frame.frameCoordinates[3].u = ((frameX + index_X) / textureWidth);
		frame.frameCoordinates[3].v = ((frameY + index_Y) / textureHeigth);

		_totalFrames.push_back(frame);
		index_X += spriteWidth;

		if (i > 0)
		{
			if (i % counColumnas == 0)
			{
				index_Y += spriteHeigth;
				_animations.push_back(_totalFrames);
				_totalFrames.clear();
			}
		}
	}
}
void Animation::addFrame(float frameX, float frameY, int spriteWidth, int spriteHeigth, int textureWidth, int textureHeigth, float timeToAnim, int totalFrames, int counColumnas, int indexFila)
{
	int miliseconds = 1000;
	_length = timeToAnim * miliseconds;

	float index_X = 0;
	float index_Y = indexFila * spriteHeigth;
	Frame frame;
	for (int i = 0; i < totalFrames; i++) {
		//--------
		frame.frameCoordinates[0].u = ((frameX + index_X) / textureWidth);
		frame.frameCoordinates[0].v = ((spriteHeigth + index_Y) / textureHeigth);

		frame.frameCoordinates[1].u = (((frameX + index_X) + spriteWidth) / textureWidth);
		frame.frameCoordinates[1].v = ((spriteHeigth + index_Y) / textureHeigth);

		frame.frameCoordinates[2].u = (((frameX + index_X) + spriteWidth) / textureWidth);
		frame.frameCoordinates[2].v = ((frameY + index_Y) / textureHeigth);

		frame.frameCoordinates[3].u = ((frameX + index_X) / textureWidth);
		frame.frameCoordinates[3].v = ((frameY + index_Y) / textureHeigth);

		_totalFrames.push_back(frame);
		index_X += spriteWidth;

		
		
		
	}
	_animations.push_back(_totalFrames);
	_totalFrames.clear();
}
void Animation::addFrame(float frameX, float frameY, int spriteWidth, int spriteHeigth, int textureWidth, int textureHeigth, float timeToAnim)
{
	_length = timeToAnim;

	Frame frame;

	frame.frameCoordinates[0].u = ((frameX) / textureWidth);
	frame.frameCoordinates[0].v = ((spriteHeigth + frameY) / textureHeigth);


	frame.frameCoordinates[1].u = (((frameX)+spriteWidth) / textureWidth);
	frame.frameCoordinates[1].v = ((spriteHeigth + frameY) / textureHeigth);

	frame.frameCoordinates[2].u = (((frameX)+spriteWidth) / textureWidth);
	frame.frameCoordinates[2].v = ((frameY) / textureHeigth);

	frame.frameCoordinates[3].u = ((frameX) / textureWidth);
	frame.frameCoordinates[3].v = ((frameY) / textureHeigth);

	_totalFrames.push_back(frame);
}

void Animation::addAnimation()
{
	if (_totalFrames.size() > 0)
	{
		_animations.push_back(_totalFrames);
		_totalFrames.clear();
	}
}
int Animation::getCurrentFrame()
{
	return _currentFrame;
}

void Animation::setCurrentAnimation(int currentAnimation) {
	_currentAnimation = currentAnimation;
}

vector<Frame>& Animation::getAnimation()
{
	if (_currentAnimation < _animations.size())
		return _animations[_currentAnimation];

	return _animations[_animations.size() - 1];
}