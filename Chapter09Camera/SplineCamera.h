#pragma once
#include "CameraComponent.h"
#include <vector>

struct Spline
{
	// control pts for spline
	// (requires n+2 points when n is number of points in segment)
	std::vector<Vector3> mControlPoints;
	// given splien segment where startIdx = p1
	// copute position based on t value
	Vector3 Compute(size_t startIdx, float t) const;
	// returns num of control path
	size_t GetNumPoints() const { return mControlPoints.size(); }
};

class SplineCamera : public CameraComponent
{
public:
	SplineCamera(class Actor* owner);

	void Update(float deltatime) override;
	//restart the spline
	void Restart();

	void SetSpeed(float speed) { mSpeed = speed; }
	void SetSpline(const Spline& spline) { mPath = spline; }
	void SetPaused(bool pause) { mPaused = pause; }
private:
	//spline path camera follows
	Spline mPath;
	// cur control point index and t
	size_t mIndex;
	float mT;
	// amout t changes/sec
	float mSpeed;
	// wheter to move the camera long the path
	bool mPaused;
};