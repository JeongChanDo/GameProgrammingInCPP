#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = mOwner->GetRotation();
		float angle = mAngularSpeed * deltaTime;

		// z�����θ� ȸ���ϱ� ���� ����
		Quaternion inc(Vector3::UnitZ, angle);

		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}

	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed))
	{
		Vector3 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		// �¿� �̵� �ӵ��� ���� ��ġ ����
		pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}