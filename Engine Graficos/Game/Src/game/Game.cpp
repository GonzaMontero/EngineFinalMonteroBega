#include "Game.h"
#include <iostream>

Game::Game()
{
	triangleAuto = Shape(ShapeType::Triangle);
	squareAuto = Shape(ShapeType::Square);
	shape = Shape(ShapeType::Square);
}

void Game::Play()
{
	EngineInit(800,600,"MY EPIC FAIL");
	UpdateEngine();
}
enum State
{
	Sleft, Sright, Sup, Sdown
};
State linkState = Sdown;
void Game::Start()
{
	
	SpriteStart();
	//ShapeStart();

	
}
float a = 0.0f;
bool right = true;
float x = 0.0f;
float y = 0.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;
float scaleZ = 1.0f;
const float valueModif = 0.001f;
float cameraX = 1.0f;
float cameraY = 1.0f;
float cameraZ = 1.0f;
float cameraSpeedRotateX = 1.17f;
float cameraSpeedRotateY = 1.17f;
void Game::Update()
{

	Input(KEYCODE_F, x, -valueModif);
	Input(KEYCODE_H, x, +valueModif);

	Input(KEYCODE_G, y, -valueModif);
	Input(KEYCODE_T, y, +valueModif);

	Input(KEYCODE_K, scaleY, -valueModif* 10.0f);
	Input(KEYCODE_I, scaleY, +valueModif* 10.0f);

	Input(KEYCODE_J, scaleX, -valueModif* 10.0f);
	Input(KEYCODE_L, scaleX, +valueModif* 10.0f);

	Input(KEYCODE_U, scaleZ, -valueModif* 10.0f);
	Input(KEYCODE_O, scaleZ, +valueModif* 10.0f);

	SpriteUpdate();


	if (GetKey(KEYCODE_W))
		CameraMove(CameraDirection::front, 1.0f);
	if (GetKey(KEYCODE_S))
		CameraMove(CameraDirection::back, 1.0f);

	if (GetKey(KEYCODE_A))
		CameraMove(CameraDirection::left, 1.0f);
	if (GetKey(KEYCODE_D))
		CameraMove(CameraDirection::right, 1.0f);

	if (GetKey(KEYCODE_Q))
		CameraMove(CameraDirection::up, 1.0f);
	if (GetKey(KEYCODE_E))
		CameraMove(CameraDirection::down, 1.0f);


	if (GetKey(KEYCODE_KP_6))
		CameraRotate(cameraSpeedRotateX, 0);
	if (GetKey(KEYCODE_KP_2))
		CameraRotate(0, cameraSpeedRotateY);
	if (GetKey(KEYCODE_KP_4))
		CameraRotate(-cameraSpeedRotateX, 0);
	if (GetKey(KEYCODE_KP_8))
		CameraRotate(0, -cameraSpeedRotateY);


	if (right)a += 0.0001f;
	else a -= 0.0001f;
	if (a > 4.0f) right = false;
	else if (a < 0.0f) right = true;

	//ShapeUpdate();

	if (GetKey(KEYCODE_SPACE))
	{		
		SetCameraProjection(CameraProjection::perspective);
		link.SetPosition(1.01f, 1.01f, 0.2f);
	}
	else
	{
		SetCameraProjection(CameraProjection::ortho);

	}

	SpriteDraw();
	//ShapeDraw();
}
bool Game::Input(int keycode,float &variable,float modif)
{
	if (GetKey(keycode))
	{

		variable += modif;
		return true;
	}
	return false;
}
void Game::Delete()
{
	if (rightAnim) delete rightAnim;
	if(leftAnim) delete leftAnim;
	if(upAnim) delete upAnim;
	if(downAnim) delete downAnim;
	if(idleRightAnim) delete idleRightAnim;
	if(idleUpAnim) delete idleUpAnim;
	if(idleLeftAnim) delete idleLeftAnim;
	if(idleDownAnim) delete idleDownAnim;
}
void Game::ShapeStart()
{
	triangleAuto.SetPosition(0.0f, 0.0f, 0.0f);
	shape.SetPosition(-5.0f,0.0f,0.0f);
}
void Game::SpriteStart()
{

	SetCameraPosition(cameraX, cameraY, cameraZ);

	itsfineSprite = Sprite("assets/This_Is_Fine.png");
	dog = Sprite("assets/logo.png");
	//ncat = Sprite("assets/logoCat.png");
	//link = Sprite("assets/test.png");
	link = Sprite("assets/link.png");
	dog.canCollision = true;
	link.canCollision = true;
	link.strength = 0;
	rightAnim = new Animation();
	rightAnim->AddFrame(0, 0, 96, 104, 961, 831, 0.001, 10);
	//rightAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	upAnim = new Animation();
	upAnim->AddFrame(0, 103, 96, 104, 961, 831, 0.001, 10);
	//upAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	leftAnim = new Animation();
	leftAnim->AddFrame(2, 208, 96, 102, 961, 831, 0.001, 10);
	//leftAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	downAnim = new Animation();
	downAnim->AddFrame(2, 312, 96, 102, 961, 831, 0.001, 10);
	//downAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	idleRightAnim = new Animation();
	idleRightAnim->AddFrame(2, 415, 96, 102, 961, 831, 0.007, 3);
	//idleRightAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	idleUpAnim = new Animation();
	idleUpAnim->AddFrame(2, 517, 96, 102, 961, 831, 0.007, 1);
	//idleUpAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	idleLeftAnim = new Animation();
	idleLeftAnim->AddFrame(2, 620, 96, 102, 961, 831, 0.007, 3);
	//idleLeftAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	idleDownAnim = new Animation();
	idleDownAnim->AddFrame(2, 723, 96, 102, 961, 831, 0.007, 3);
	//idleDownAnim->AddFrame(0, 0, 50, 50, 50, 50, 10, 1);
	link.SetAnimation(idleDownAnim);

	//itsfineSprite.SetPosition(0.0f, 0.0f, 2.0f);
	//itsfineSprite.Scale(1.0f, 1.0f, 1.0f);
	//dog.SetPosition(-3.5f, 0.0f, -1.0f);
	//dog.Scale(1.0f, 1.0f, 1.0f);
	//ncat.SetPosition(-2.5f, 0.0f, 0.0f);
	//ncat.Scale(0.006f, 0.006f, 1.0f);
	link.SetPosition(1.01f, 1.01f, 0.2f);
	link.Scale(0.1f, 0.1f, 1.0f);


	mytilemap = new Tilemap();
	mytilemap->importTileMap("assets/Tilemap21.tmx");

}
void Game::ShapeUpdate()
{

	triangleAuto.Rotate(a,a,a);
	triangleAuto.Scale(0.1f+a,1.0f,1.0f);
	triangleAuto.SetPosition(+a-2.0f, -1.5f, -5.0f);
	triangleAuto.SetColor(0.0f,0.3f,0.8f);
	
	squareAuto.Rotate(0.0f,0.0f,a);
	squareAuto.SetPosition(-1.9f,+1.5f,-5.0f);
	squareAuto.SetColor(0.0f,1.0f,0.0f);
	
	shape.SetPosition(x, y, -4.0f);
	
	shape.Scale(scaleX, scaleY, scaleZ);
}
void Game::SpriteUpdate()
{
	if (GetKey(KEYCODE_1))
	{
		linkState = Sleft;
		link.SetAnimation(leftAnim);
		link.SetPosition(link.GetPositionX() - 0.01f, link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sleft)
	{
		link.SetAnimation(idleLeftAnim);
	}
	if (GetKey(KEYCODE_2))
	{
		linkState = Sright;
		link.SetAnimation(rightAnim);
		link.SetPosition(link.GetPositionX() + 0.01f, link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sright)
	{
		link.SetAnimation(idleRightAnim);
	}
	if (GetKey(KEYCODE_3))
	{
		linkState = Sup;
		link.SetAnimation(upAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() + 0.01f, link.GetPositionZ());
	}
	else if (linkState == Sup)
	{
		link.SetAnimation(idleUpAnim);
	}
	if (GetKey(KEYCODE_4))
	{
		linkState = Sdown;
		link.SetAnimation(downAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() - 0.01f, link.GetPositionZ());
	}
	else if (linkState == Sdown)
	{
		link.SetAnimation(idleDownAnim);
	}

	if (GetKey(KEYCODE_8))
	{
		link.Scale(link.GetScaleX()+0.01f, link.GetScaleY() + 0.01f ,1.0f);
	}
	if (GetKey(KEYCODE_9))
	{
		link.Scale(link.GetScaleX() - 0.01f, link.GetScaleY() - 0.01f , 1.0f);
	}


	mytilemap->checkCollision(link);
	//ncat.SetPosition(link.GetPositionX(),link.GetPositionY(),link.GetPositionZ()-0.0000001f);
	link.Update();
}
void Game::SpriteDraw()
{
	
	//itsfineSprite.Draw();
	//dog.Draw();
	//ncat.Draw();
	mytilemap->draw();

	link.Draw();

}
void Game::ShapeDraw()
{
	triangleAuto.Draw();
	squareAuto.Draw();
	shape.Draw();

}