#include "OrbitActor.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "OrbitCamera.h"
#include "MoveComponent.h"

OrbitActor::OrbitActor(Game* game)
	:Actor(game)
{
	mMeshComp = new MeshComponent(this);
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));
	mCameraComp = new OrbitCamera(this);
}

void OrbitActor::ActorInput(const uint8_t* keys)
{
	// mouse rot
	// get relative movement from sdl
	int x, y;
	Uint32 buttons = SDL_GetRelativeMouseState(&x, &y);
	//only apply rot if right-click is held)
	if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		//assume mouse movement is usally between -500 ~ 500
		const int maxMouseSpeed = 500;
		// rot/sec at maximum speed
		const float maxOrbitSpeed = Math::Pi * 8;
		float yawSpeed = 0.0f;

		if (x != 0)
		{
			//convert -1.0 ~ 1.0
			yawSpeed = static_cast<float>(x) / maxMouseSpeed;
			// multiply by rot/sec
			yawSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetYawSpeed(-yawSpeed);

		// compute pitch
		float pitchSpeed = 0.0f;
		if (y != 0)
		{
			//convert to -1.0 ~1.0
			pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetPitchSpeed(pitchSpeed);
	}
}

void OrbitActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}