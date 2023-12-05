#include "Ship.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "InputSystem.h"

Ship::Ship(Game* game)
	:Actor(game)
	, mSpeed(400.0f)
	, mLaserCooldown(0.0f)
{
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;

	/*
	Vector2 pos = GetPosition();
	pos += mVelocityDir * mSpeed * deltaTime;
	SetPosition(pos);

	float angle = Math::Atan2(mRotationDir.y, mRotationDir.x);
	SetRotation(angle);
	*/
}

void Ship::ActorInput(const InputState& state)
{
	if (state.Mouse.GetButtonState(SDL_BUTTON_LEFT) == EPressed
		&& mLaserCooldown <= 0.0f)
	{
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		mLaserCooldown = 0.25f;
	}

	/*
	bool pressedW = state.Keyboard.GetKeyValue(SDL_SCANCODE_W);
	bool pressedS = state.Keyboard.GetKeyValue(SDL_SCANCODE_S);
	bool pressedA = state.Keyboard.GetKeyValue(SDL_SCANCODE_A);
	bool pressedD = state.Keyboard.GetKeyValue(SDL_SCANCODE_D);
	
	bool keyboardPressed = pressedW && pressedS && pressedA && pressedD;
	if (keyboardPressed)
	{
		if (pressedW)
			mVelocityDir = Vector2();
	}
	*/
}