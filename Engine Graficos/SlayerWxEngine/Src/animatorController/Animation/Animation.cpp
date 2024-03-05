#include "Animation.h"
#include "globalUtility/globalUtility.h"
#include <iostream>
using namespace std;
Animation::Animation()
{
	currentFrame = 0;
	currentTime = 0;
}
Animation::~Animation()
{

}

void Animation::AddFrame(float xFrame, float yFrame, float widthFrame, float heightFrame, float textureWidth, float textureHegiht, float durationInSec)
{
	length = lengthMultiply * durationInSec;

	Frame frame;
	frame.coords[0].U = (xFrame/textureWidth);
	frame.coords[0].V = (yFrame/textureHegiht);

	frame.coords[1].U = (xFrame + widthFrame/ textureWidth);
	frame.coords[1].V = frame.coords[0].V;

	frame.coords[2].U = frame.coords[0].U;
	frame.coords[2].V = (yFrame + heightFrame / textureHegiht);

	frame.coords[3].U = frame.coords[1].U;
	frame.coords[3].V = frame.coords[2].V;
	myFrames.push_back(frame);
}
void Animation::AddFrame(float xFrame, float yFrame, float widthFrame, float heightFrame, float textureWidth, float textureHegiht, float durationInSec,int frameCount)
{
	length = lengthMultiply * durationInSec;


	float frameXIndex = 0;


	for (int i = 0; i < frameCount; i++)
	{
		Frame frame;
		frame.coords[0].U = ((xFrame + frameXIndex) / textureWidth);
		frame.coords[0].V = (yFrame / textureHegiht);
		frame.coords[1].U = (((xFrame + frameXIndex)+ widthFrame) / textureWidth);
		frame.coords[1].V = (yFrame / textureHegiht);

		frame.coords[2].U = ((xFrame + frameXIndex) / textureWidth);
		frame.coords[2].V = ((yFrame + heightFrame) / textureHegiht);

		frame.coords[3].U = (((xFrame + frameXIndex) + widthFrame) / textureWidth);
		frame.coords[3].V = ((yFrame + heightFrame) / textureHegiht);
		myFrames.push_back(frame);

		//cout << "~~~~~~~~~~~~~~~~~~~~~ Frame "<< i+1 <<" ~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		//cout << frame.coords[2].U << " * " << frame.coords[3].U << endl;
		//cout << frame.coords[0].U << " * " << frame.coords[1].U << endl;
		frameXIndex += widthFrame;
	}
	//cout << "~~~~~~~~~~~~~~~~ END ANIM ~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void Animation::Update()
{
	currentTime += DeltaTime();
	while (currentTime > length)
	{
		currentTime -= length;
	}
	currentFrame = static_cast<int>(currentTime/(length / myFrames.size()));
}
