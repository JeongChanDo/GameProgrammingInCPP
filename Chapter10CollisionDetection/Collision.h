#pragma once
#include "Math.h"
#include <vector>

struct LineSegment
{
	LineSegment(const Vector3& start, const Vector3& end);
	//get point along segment
	Vector3 PointOnSegment(float t) const;
	// get minimum dist squared between point and line segment
	float MinDistSq(const Vector3& point) const;
	// get mindistsq between two line segments
	static float MinDistSq(const LineSegment& s1, const LineSegment& s2);

	Vector3 mStart;
	Vector3 mEnd;
};

struct Plane
{
	Plane(const Vector3& normal, float d);
	// construct plane from three points;
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);
	// get the signed distance between the point and the plane
	float SignedDist(const Vector3& point) const;
	
	Vector3 mNormal;
	float mD;
};


struct Sphere
{
	Sphere(const Vector3& center, float radius);
	bool Contains(const Vector3& point) const;

	Vector3 mCenter;
	float mRadius;
};

//�� ���� �ٿ�� �ڽ�
struct AABB
{
	AABB(const Vector3& min, const Vector3& max);
	//update min and max accounting for this point
	//(used when loading a model)
	void UpdateMinMax(const Vector3& point);
	// rotated by a quaternion
	void Rotate(const Quaternion& q);
	bool Contains(const Vector3& point) const;
	float MinDistSq(const Vector3& point) const;

	Vector3 mMin;
	Vector3 mMax;
};

// aabb���� �浹 ������� �ʹ� ŭ
struct OBB
{
	Vector3 mCenter;
	Quaternion mRotation;
	Vector3 eExtents;
};

struct Capsule
{
	Capsule(const Vector3& start, const Vector3& end, float radius);
	// get point along segment where 0 <= t <= 1
	Vector3 PointOnSegment(float t)  const;
	bool Contains(const Vector3& point) const;

	LineSegment mSegment;
	float mRadius;
};

struct ConvexPolygon
{
	bool Contains(const Vector2& point) const;
	//vertices have a clockwise ordering
	std::vector<Vector2> mVertices;
};

bool Intersect(const Sphere& a, const Sphere& b);
bool Intersect(const AABB& a, const AABB& b);
bool Intersect(const Capsule& a, const Capsule& b);
bool Intersect(const Sphere& s, const AABB& box);


bool Intersect(const LineSegment& l, const Sphere& s, float& outT);
bool Intersect(const LineSegment& l, const Plane& P, float& outT);
bool Intersect(const LineSegment& l, const AABB& b, float& outT, Vector3& outNorm);

bool SweptSphere(const Sphere& P0, const Sphere& P1,
	const Sphere& Q0, const Sphere& Q1, float& t);