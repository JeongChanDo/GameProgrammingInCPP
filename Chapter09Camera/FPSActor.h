#pragma once
#include "Actor.h"

class FPSActor : public Actor
{
public:
	FPSActor(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keys) override;

	void SetVisible(bool visible);
private:
	class MoveComponent* mMoveComp;
	class MeshComponent* mMeshComp;
	class FPSCamera* mCameraComp;
	class Actor* mFPSModel;
};