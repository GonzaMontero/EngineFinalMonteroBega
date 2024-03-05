#include "baseGame/BaseGame.h"
#include "AnimatorController/Animation/Animation.h"
#include "tilemap/Tilemap.h"
class Game : public BaseGame
{
private:
	Shape triangleAuto;
	Shape squareAuto;
	Shape shape;
	Sprite itsfineSprite;
	Sprite dog;
	Sprite ncat;
	Sprite link;
	void Start();
	void Update();
	bool Input(int keycode, float &variable, float modif);
	void Delete();
	Animation* leftAnim;
	Animation* rightAnim;
	Animation* upAnim;
	Animation* downAnim;
	Animation* idleRightAnim;
	Animation* idleUpAnim;
	Animation* idleLeftAnim;
	Animation* idleDownAnim;
	void SpriteStart();
	void ShapeStart();
	void SpriteUpdate();
	void ShapeUpdate();
	void SpriteDraw();
	void ShapeDraw();

	Tilemap* mytilemap;
public:
	Game();
	void Play();
};
