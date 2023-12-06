#pragma once
#include "Component.h"
#include "Collision.h"

class BoxComponent : public Component
{
public:
	BoxComponent(class Actor* owner, int updateOrder = 100);
	~BoxComponent();

	void OnUpdateWorldTransform() override;

	void SetObjectBox(const AABB& model) { mObjectBox = model; }
	const AABB& GetWorldBox() const { return mWorldBox; }

	void SetShouldRotate(bool value) { mShouldRotate = value; }
private:
	// 오브젝트 공간 경계용 AABB. 초기화 된후 변경 안되어야함
	AABB mObjectBox;
	// 세계 공간 경계 AABB. 액터의 세계 변환이 바뀔때마다 변경됨, 위 mObjectBox 사용해서 갱신
	AABB mWorldBox;
	// 세계 회전에 따라 회전시켜야하는지 다룸
	bool mShouldRotate;
};