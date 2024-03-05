#include "Sprite.h"
#include <iostream>
Sprite::Sprite() : Entity2D()
{
	currentFrameIndex = 1;
	previousFrameIndex = 99;
}

Sprite::Sprite(const char* filePath) : Entity2D()
{
	data = TextureImporter::ImportTexture(filePath);
	if(data.nrChannels == 4)
	alpha = true;
	currentFrameIndex = 1;
	previousFrameIndex = 99;
}

void Sprite::SetAnimation(Animation* anim)
{
	actualAnim = anim;
	currentFrameIndex = 0;
	SetTextureCoordinate(actualAnim->myFrames[currentFrameIndex].coords[0].U,
		actualAnim->myFrames[currentFrameIndex].coords[0].V,
		actualAnim->myFrames[currentFrameIndex].coords[1].U,
		actualAnim->myFrames[currentFrameIndex].coords[1].V,
		actualAnim->myFrames[currentFrameIndex].coords[2].U,
		actualAnim->myFrames[currentFrameIndex].coords[2].V,
		actualAnim->myFrames[currentFrameIndex].coords[3].U,
		actualAnim->myFrames[currentFrameIndex].coords[3].V);
	previousFrameIndex = std::numeric_limits<unsigned int>::max_digits10;
}

Animation* Sprite::GetAnimation()
{
	return actualAnim;
}

void Sprite::Update()
{
	lastPosition = position;

	if (!actualAnim)
		return;

	actualAnim->Update();
	currentFrameIndex = actualAnim->currentFrame;
	if (currentFrameIndex != previousFrameIndex && currentFrameIndex < actualAnim->myFrames.size())
	{
		SetTextureCoordinate(actualAnim->myFrames[currentFrameIndex].coords[0].U,
							 actualAnim->myFrames[currentFrameIndex].coords[0].V,
							 actualAnim->myFrames[currentFrameIndex].coords[1].U,
							 actualAnim->myFrames[currentFrameIndex].coords[1].V,
							 actualAnim->myFrames[currentFrameIndex].coords[2].U,
							 actualAnim->myFrames[currentFrameIndex].coords[2].V,
							 actualAnim->myFrames[currentFrameIndex].coords[3].U,
							 actualAnim->myFrames[currentFrameIndex].coords[3].V);

		previousFrameIndex = currentFrameIndex;
	}
}

void Sprite::Draw()
{
	TextureImporter::BindTexture(data.texture);
	renderer->SpriteDraw(vertexSprite, vertexLength, index, indexLength, model,alpha);
}

void Sprite::SetTextureCoordinate(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3)
{
	vertexSprite[7] = u3; //right
	vertexSprite[8] = v3; //up
					  
	vertexSprite[16] =  u1; //right 
	vertexSprite[17] =  v1; //down
					  
	vertexSprite[25] =  u0; //left   
	vertexSprite[26] =  v0; //down      
					  
	vertexSprite[34] =  u2; //left
	vertexSprite[35] =  v2; //up
}

void Sprite::SetDataTexture(TextureData newData)
{
	data = newData;
}

void Sprite::SetColor(float r, float g, float b)
{
	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;
	vertexSprite[3] = r;
	vertexSprite[4] = g;
	vertexSprite[5] = b;
	vertexSprite[12] = r;
	vertexSprite[13] = g;
	vertexSprite[14] = b;
	vertexSprite[21] = r;
	vertexSprite[22] = g;
	vertexSprite[23] = b;
	vertexSprite[30] = r;
	vertexSprite[31] = g;
	vertexSprite[32] = b;

}