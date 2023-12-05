#pragma once
#include "CameraComponent.h"

class FollowCamera : public CameraComponent
{
public:
	FollowCamera(class Actor* owner);

	void Update(float deltaTime) override;

	void SnapToIdeal();

	void SetHorzDist(float dist) { mHorzDist = dist; }
	void SetVertDist(float dist) { mVertDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	void SetSpringConstant(float spring) { mSpringConstant = spring; }
private:
	Vector3 ComputeCameraPos() const;

	//actual pos of camera
	Vector3 mActualPos;
	// vel of actual camera
	Vector3 mVelocity;
	// horizontal follow dist
	float mHorzDist;
	//vertical follow dist
	float mVertDist;
	// target dist
	float mTargetDist;
	// sprint const (higher is more stiff)
	float mSpringConstant;
};