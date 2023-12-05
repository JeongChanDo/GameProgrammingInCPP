#include "FPSActor.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "Game.h"
#include "FPSCamera.h"
#include "MeshComponent.h"

FPSActor::FPSActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
	mCameraComp = new FPSCamera(this);
	mFPSModel = new Actor(game);
	mFPSModel->SetScale(0.75f);
	mMeshComp = new MeshComponent(mFPSModel);
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Rifle.gpmesh"));
}

void FPSActor::UpdateActor(float deltaTime)
{
	//Update position of fps model relative to actor position
	const Vector3 modelOffset(Vector3(10.0f, 10.0f, -10.0f));
	Vector3 modelPos = GetPosition();
	modelPos += GetForward() * modelOffset.x;
	modelPos += GetRight() * modelOffset.y;
	modelPos.z = modelOffset.z;
	mFPSModel->SetPosition(modelPos);

	// init rotation to actor rot
	Quaternion q = GetRotation();

	// rote by pitch from camera
	q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCameraComp->GetPitch()));
	mFPSModel->SetRotation(q);
}


void FPSActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	//wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		strafeSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += 400.0f;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);


	// mouse movement
	//get relative movement from sdl
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	// assume mouse movement is usually between -500 ~ 500
	const int maxMouseSpeed = 500;
	// rotation/sec at maximum speed
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		//convert to -1.0 ~ 1.0
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		// multiply by rot/sec
		angularSpeed *= maxAngularSpeed;
	}
	mMoveComp->SetAngularSpeed(angularSpeed);

	//Compute pitch
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		//convert -1.0 ~ 1.0
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	mCameraComp->SetPitchSpeed(pitchSpeed);
}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}