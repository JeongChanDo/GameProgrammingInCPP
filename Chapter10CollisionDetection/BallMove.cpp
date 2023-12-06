#include "BallMove.h"
#include "Actor.h"
#include "Game.h"
#include "PhysWorld.h"
#include "BallActor.h"

BallMove::BallMove(Actor* owner)
	:MoveComponent(owner)
{

}

void BallMove::Update(float deltaTime)
{
	//construct segment in direction of travel
	// �̵� �������� ���� ����
	const float segmentLength = 30.0f;
	Vector3 start = mOwner->GetPosition();
	Vector3 dir = mOwner->GetForward();
	Vector3 end = start + dir * segmentLength;
	LineSegment ls(start, end);

	// ���а� ���� ���� �׽�Ʈ ����
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();
	PhysWorld::CollisionInfo info;
	if (phys->SegmentCast(ls, info))
	{
		//�浹�� ǥ�� ���� �������� �ݻ�
		dir = Vector3::Reflect(dir, info.mNormal);
		mOwner->RotateToNewForward(dir);
	}

	//���� �ӵ��� ��Ÿ �ð����� ���̽� Ŭ���� �̵� ����
	MoveComponent::Update(deltaTime);
}