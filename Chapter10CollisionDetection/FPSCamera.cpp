#include "FPSCamera.h"
#include "Actor.h"

FPSCamera::FPSCamera(Actor* owner)
	:CameraComponent(owner)
	,mPitchSpeed(0.0f)
	,mMaxPitch(Math::Pi / 3.0f)
	,mPitch(0.0f)
{

}

//��ġ ����
void FPSCamera::Update(float deltaTime)
{
	//call parent update(doesn't do anything right now)
	CameraComponent::Update(deltaTime);
	//camera pos is owner pos
	Vector3 cameraPos = mOwner->GetPosition();


	//update pitch based on pitch speed
	mPitch += mPitchSpeed * deltaTime;
	// clamp pitch to -max ~ +max
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
	// make quaternion representing pitch rotation
	// which is about owner's right vector
	Quaternion q(mOwner->GetRight(), mPitch);

	// rotate owner forward by pitch quaternion
	Vector3 viewForward = Vector3::Transform(
		mOwner->GetForward(), q);

	//Ÿ���� ������ 100 ���� �տ� �ִ� ����
	Vector3 target = cameraPos + viewForward * 100.0f;
	// �������� z ���� ����
	Vector3 up = Vector3::UnitZ;
	// look at ����� �����Ͽ� �� ��� ����
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}