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
	// 이동 방향으로 선분 생성
	const float segmentLength = 30.0f;
	Vector3 start = mOwner->GetPosition();
	Vector3 dir = mOwner->GetForward();
	Vector3 end = start + dir * segmentLength;
	LineSegment ls(start, end);

	// 선분과 게임 세계 테스트 진행
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();
	PhysWorld::CollisionInfo info;
	if (phys->SegmentCast(ls, info))
	{
		//충돌시 표면 법선 기준으로 반사
		dir = Vector3::Reflect(dir, info.mNormal);
		mOwner->RotateToNewForward(dir);
	}

	//전진 속도와 델타 시간으로 베이스 클레스 이동 갱신
	MoveComponent::Update(deltaTime);
}