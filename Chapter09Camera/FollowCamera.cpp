#include "FollowCamera.h"
#include "Actor.h"

FollowCamera::FollowCamera(Actor* owner)
	:CameraComponent(owner)
	, mHorzDist(350.0f)
	, mVertDist(150.0f)
	, mTargetDist(100.0f)
	, mSpringConstant(64.0f)
{
	

}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	// ������ ��������� ����(����) �� ���
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	// compute ideal pos
	Vector3 idealPos = ComputeCameraPos();
	// compute diff between actual and ideal
	Vector3 diff = mActualPos - idealPos;
	// compute acceleration of spring
	Vector3 acel = -mSpringConstant * diff
		- dampening * mVelocity;
	//update velocity
	mVelocity += acel * deltaTime;
	// update actual cam pos
	mActualPos += mVelocity * deltaTime;

	// target is tart dist in front of owning actor
	Vector3 target = mOwner->GetPosition()
		+ mOwner->GetForward() * mTargetDist;
	// ī�޶� ���������� ��� �����Ƿ����� unit z
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	// set auctal pos to ideal
	mActualPos = ComputeCameraPos();
	// zero vel
	mVelocity = Vector3::Zero;
	// target is tart dist in front of owning actor
	Vector3 target = mOwner->GetPosition()
		+ mOwner->GetForward() * mTargetDist;
	// ī�޶� ���������� ��� �����Ƿ����� unit z
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
	SetViewMatrix(view);
}

Vector3 FollowCamera::ComputeCameraPos() const
{
	//set camera pos behind and above owner
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}