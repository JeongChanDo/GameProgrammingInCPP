#include "FPSActor.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "Game.h"
#include "FPSCamera.h"
#include "MeshComponent.h"
#include "BallActor.h"
#include "BoxComponent.h"
#include "PlaneActor.h"

FPSActor::FPSActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
	mCameraComp = new FPSCamera(this);
	mFPSModel = new Actor(game);
	mFPSModel->SetScale(0.75f);
	mMeshComp = new MeshComponent(mFPSModel);
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Rifle.gpmesh"));

	mBoxComp = new BoxComponent(this);
	AABB myBox(Vector3(-25.0f, -25.0f, -87.5f),
		Vector3(25.0f, 25.0f, 87.5f));
	mBoxComp->SetObjectBox(myBox);
	mBoxComp->SetShouldRotate(false);
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	FixCollision();

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

void FPSActor::Shoot()
{
	//Get start point (in center of screen on near plane)
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = GetGame()->GetRenderer()->Unproject(screenPoint);
	//get end point (in center of screen, between near and far
	screenPoint.z = 0.9f;
	Vector3 end = GetGame()->GetRenderer()->Unproject(screenPoint);
	//get direction vector
	Vector3 dir = end - start;
	dir.Normalize();
	// spawn a ball
	BallActor* ball = new BallActor(GetGame());
	ball->SetPlayer(this);
	ball->SetPosition(start + dir * 20.0f);
	// rotate the ball to face new direction
	ball->RotateToNewForward(dir);

}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}

void FPSActor::FixCollision()
{
	//need to recompyte my world tf to update worldbox
	ComputeWorldTransform();

	const AABB& playerBox = mBoxComp->GetWorldBox();
	Vector3 pos = GetPosition();
	
	auto& planes = GetGame()->GetPlanes();
	for (auto pa : planes)
	{
		// do we collide with this planeactor?
		const AABB& planeBox = pa->GetBox()->GetWorldBox();
		if (Intersect(playerBox, planeBox))
		{
			//calculate all diffs
			float dx1 = planeBox.mMax.x - playerBox.mMin.x;
			float dx2 = planeBox.mMin.x - playerBox.mMax.x;
			float dy1 = planeBox.mMax.y - playerBox.mMin.y;
			float dy2 = planeBox.mMin.y - playerBox.mMax.y;
			float dz1 = planeBox.mMax.z - playerBox.mMin.z;
			float dz2 = planeBox.mMin.z - playerBox.mMax.z;

			//set dx to whichever of dx1, dx2 have a lower abs
			float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
			float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
			float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;


			// whichever is closet, adjust xyz pos
			if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
			{
				pos.x += dx;
			}
			else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
			{
				pos.y += dy;
			}
			else
			{
				pos.z += dz;
			}

			SetPosition(pos);
			mBoxComp->OnUpdateWorldTransform();
		}
	}
}