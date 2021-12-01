#ifndef ANIMATION_H
#define ANIMATION_H
#include "export.h"
#include "Frame.h"
#include "TimeManager.h"
#include <vector>
#include <algorithm>

using namespace std;

class ENGINE_API Animation {
	int _currentFrame;
	float _currentTime;
	float _length;
	int _acumulationWidth;
	int _acumulationHeighth;
	vector<Frame> _totalFrames;
	vector<vector<Frame>> _animations;
	int _currentAnimation = 0;
	float* _vertex;
public:
	Animation();
	~Animation();
	void update(Time& time);
	void addFrame(float frameX, float frameY, int spriteWidth, int spriteHeigth, int textureWidth, int textureHeigth, float timeToAnim, int totalFrames, int countFilas);
	int getCurrentFrame();
	vector<Frame>& getAnimation();
	void setCurrentAnimation(int currentAnimation);
	void addFrame(float frameX, float frameY, int spriteWidth, int spriteHeigth, int textureWidth, int textureHeigth, float timeToAnim);
	void addAnimation();
};
#endif // !ANIMATION_H