#include "FPSCamera.h"
#include "Actor.h"

FPSCamera::FPSCamera(Actor* owner)
	:CameraComponent(owner)
	,mPitchSpeed(0.0f)
	,mMaxPitch(Math::Pi / 3.0f)
	,mPitch(0.0f)
{

}

//피치 있음
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

	//타깃은 소유자 100 단위 앞에 있다 가정
	Vector3 target = cameraPos + viewForward * 100.0f;
	// 상향축은 z 단위 벡터
	Vector3 up = Vector3::UnitZ;
	// look at 행렬을 생성하여 뷰 행렬 설정
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}