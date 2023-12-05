#include "CameraActor.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "Game.h"

CameraActor::CameraActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
}

void CameraActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//compute new camera from this actor	
	Vector3 cameraPos = GetPosition();

	// ī�޶� �տ� 100 ���� ������ ��
	Vector3 target = GetPosition() + GetForward() * 100.0f;
	Vector3 up = Vector3::UnitZ;

	// view mat�� ���迡�� ī�޶� or ����ġ ���� ǥ��, look at ����� ī�޶� ��ġ,����ǥ��
	// look at ����� ���ǳ���, ���̺��� Ÿ����ġ, ���ʹ��� 3������ ���� -> 4x4 ��İ��
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}

void CameraActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::TwoPi;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angularSpeed += Math::TwoPi;
	}
	
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetAngularSpeed(angularSpeed);
}