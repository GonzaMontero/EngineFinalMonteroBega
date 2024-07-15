#ifndef SPRITE_H
#define SPRITE_H

#include "../Utils/Export.h"
#include "../Entity/Entity2D.h"
#include "../Entity/Entity.h"
#include "../Utils/TextureImporter.h"
#include "Animation.h"
#include "../Renderer/renderer.h"

namespace Engine {
	
	struct TextureData;
	class Animation;

	struct ENGINE_API UVCoordinates
	{
		float x;
		float y;
	};

	class ENGINE_API Sprite : public Entity2D 
	{
	public:
		Sprite();
		Sprite(Renderer* renderer, const char* imagePath, bool invertImage);
		~Sprite();

		void Draw() override;
		void ModifyTextureCoords(AtlasConfigurations config);
		TextureData* CreateAnimationData(const char* AtlasFilePath, bool invertImage);
		void DeleteAnimationData(TextureData* atlasToDelete);

		int CreateAnimation();
		int CreateAnimation(AtlasConfigurations config);
		int CreateAnimation(TextureData* animationData, int columns, int rows);
		int CreateAnimation(TextureData* animationData, AtlasConfigurations config);

		void AddFrameToExistingAnimation(int animationID, int positonX, int positionY, int width, int height);
		void PlayAnimation(int ID);
		void StopAnimation(int ID);
		void SetAnimationRepeat(int ID, bool active);
		void StopAllAnimations();

		void SetAnimationSpeed(int ID, float speed);
		void SetAnimationTimeBetweenFrames(int ID, float time);
		void SetAnimationFullTime(int ID, float time);
		void SetTextureCoordinates(glm::vec2 coord1, glm::vec2 coord2, glm::vec2 coord3, glm::vec2 coord4);
		void SetTexture(Renderer* renderer, const char* filePathImage, bool invertImage);

		void Denitialize();

	private:
		void SetShader(unsigned int texture);
		unsigned int GetCurrentTextureID();
		unsigned int _bufferPosUV = 0;
		int _lastCoordIndex = 0;

		UVCoordinates uvCoords[4];

		void BindUVCoords();
		void BindUVCoords(int i);

		TextureData* _baseTexture;
		std::vector<Animation*> _allAnimations;
	};
}

#endif // !SHAPE_H
