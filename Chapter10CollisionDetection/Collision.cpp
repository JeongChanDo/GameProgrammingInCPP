#include "Collision.h"
#include <algorithm>
#include <array>

LineSegment::LineSegment(const Vector3& start, const Vector3& end)
	:mStart(start)
	, mEnd(end)
{
}

Vector3 LineSegment::PointOnSegment(float t) const
{
	return mStart + (mEnd - mStart) * t;
}

float LineSegment::MinDistSq(const Vector3& point) const
{
	Vector3 ab = mEnd - mStart;
	Vector3 ba = -1.0f * ab;
	Vector3 ac = point - mStart;
	Vector3 bc = point - mEnd;

	if (Vector3::Dot(ab, ac) < 0.0f)
	{
		return ac.LengthSq();
	}
	else if (Vector3::Dot(ba, bc) < 0.0f)
	{
		return bc.LengthSq();
	}
	else
	{
		float scalar = Vector3::Dot(ac, bc) / Vector3::Dot(ab, ab);
		Vector3 p = scalar * ab;
		return (ac - p).LengthSq();
	}
}


float LineSegment::MinDistSq(const LineSegment& s1, const LineSegment& s2)
{
	Vector3   u = s1.mEnd - s1.mStart;
	Vector3   v = s2.mEnd - s2.mStart;
	Vector3   w = s1.mStart - s2.mStart;
	float    a = Vector3::Dot(u, u);         // always >= 0
	float    b = Vector3::Dot(u, v);
	float    c = Vector3::Dot(v, v);         // always >= 0
	float    d = Vector3::Dot(u, w);
	float    e = Vector3::Dot(v, w);
	float    D = a * c - b * b;        // always >= 0
	float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

	// compute the line parameters of the two closest points
	if (Math::NearZero(D)) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
	tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	Vector3   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return dP.LengthSq();   // return the closest distance squared
}


Plane::Plane(const Vector3& normal, float d)
	:mNormal(normal)
	, mD(d)
{

}

//construct plane by three points
Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
{
	//compute vectors from a to b and a to c
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	// cross product and normalize to get normal
	mNormal = Vector3::Cross(ab, ac);
	mNormal.Normalize();
	// d = -p dot n
	mD = -Vector3::Dot(a, mNormal);
}



float Plane::SignedDist(const Vector3& point) const
{
	return Vector3::Dot(point, mNormal) - mD;
}

Sphere::Sphere(const Vector3& center, float radius)
	:mCenter(center)
	,mRadius(radius)
{

}

bool Sphere::Contains(const Vector3& point) const
{
	//Get distance squared between center and point
	float distSq = (mCenter - point).LengthSq();
	return distSq <= (mRadius * mRadius);
}


AABB::AABB(const Vector3& min, const Vector3& max)
	:mMin(min)
	,mMax(max)
{

}

void AABB::UpdateMinMax(const Vector3& point)
{
	//update each component separately
	mMin.x = Math::Min(mMin.x, point.x);
	mMin.y = Math::Min(mMin.y, point.y);
	mMin.z = Math::Min(mMin.z, point.z);

	mMax.x = Math::Max(mMax.x, point.x);
	mMax.y = Math::Max(mMax.y, point.y);
	mMax.z = Math::Max(mMax.z, point.z);
}

void AABB::Rotate(const Quaternion& q)
{
	// 박스의 구석 8개 점 생성
	std::array<Vector3, 8> points;
	// min점은 항상 구석
	points[0] = mMin;
	// Min, Max점을 제외한 나머지 구석은 min점과 max 점 요소 조합으로 구함
	//2개의 min, 1개m max 구석점 생성
	points[1] = Vector3(mMax.x, mMin.y, mMin.z);
	points[2] = Vector3(mMin.x, mMax.y, mMin.z);
	points[3] = Vector3(mMin.x, mMin.y, mMax.z);
	// 2개의 max, 1min 순으로 구석점 생성
	points[4] = Vector3(mMin.x, mMax.y, mMax.z);
	points[5] = Vector3(mMax.x, mMin.y, mMax.z);
	points[6] = Vector3(mMax.x, mMax.y, mMin.z);
	// max 구석점
	points[7] = Vector3(mMax);

	//첫점 쿼터니언으로 회전
	Vector3 p = Vector3::Transform(points[0], q);

	// 회전된 첫 점으로 min max 리셋
	mMin = p;
	mMax = p;
	//남은 점들을 회전 한 뒤 min/max 갱신
	for (size_t i = 1; i < points.size(); i++)
	{
		p = Vector3::Transform(points[i], q);
		UpdateMinMax(p);
	}
}

bool AABB::Contains(const Vector3& point) const
{
	bool outside = point.x < mMin.x ||
		point.y < mMin.y ||
		point.z < mMin.z ||
		point.x > mMax.x ||
		point.y > mMax.y ||
		point.z > mMax.z;
	return !outside;
}

float AABB::MinDistSq(const Vector3& point) const
{
	//compte diffs for each axis
	float dx = Math::Max(mMin.x - point.x, 0.0f);
	dx = Math::Max(dx, point.x - mMax.x);
	float dy = Math::Max(mMin.y - point.y, 0.0f);
	dy = Math::Max(dy, point.y - mMax.y);
	float dz = Math::Max(mMin.z - point.z, 0.0f);
	dz = Math::Max(dy, point.z - mMax.z);
	// distance squared formula
	return dx * dx + dy * dy + dz * dz;
}

Capsule::Capsule(const Vector3& start, const Vector3& end, float radius)
	:mSegment(start, end)
	, mRadius(radius)
{

}

Vector3 Capsule::PointOnSegment(float t) const
{
	return mSegment.PointOnSegment(t);
}

bool Capsule::Contains(const Vector3& point) const
{
	float distSq = mSegment.MinDistSq(point);
	return distSq <= (mRadius * mRadius);
}

bool ConvexPolygon::Contains(const Vector2& point) const
{
	float sum = 0.0f;
	Vector2 a, b;
	for (size_t i = 0; i < mVertices.size() - 1; i++)
	{
		//from point to first vertex
		a = mVertices[i] - point;
		a.Normalize();
		//from point to second vertex
		b = mVertices[i + 1] - point;
		b.Normalize();
		// add angle to sum
		sum += Math::Acos(Vector2::Dot(a, b));
	}
	// have to add angle for last vertex and first vertex
	a = mVertices.back() - point;
	a.Normalize();
	b = mVertices.front() - point;
	b.Normalize();
	sum += Math::Acos(Vector2::Dot(a, b));
	// return true if approximately 2pi
	return Math::NearZero(sum - Math::TwoPi);
}

/*
교차테스트
*/

//구체간 교차
bool Intersect(const Sphere& a, const Sphere& b)
{
	float distSq = (a.mCenter - b.mCenter).LengthSq();
	float sumRadii = a.mRadius + b.mRadius;
	return distSq <= (sumRadii * sumRadii);
}


bool Intersect(const AABB& a, const AABB& b)
{
	bool no = a.mMax.x < b.mMin.x ||
		a.mMax.y < b.mMin.y ||
		a.mMax.z < b.mMin.z ||
		b.mMax.x < a.mMin.x ||
		b.mMax.y < a.mMin.y ||
		b.mMax.z < a.mMin.z;
	return !no;
}

bool Intersect(const Sphere& s, const AABB& box)
{
	float distSq = box.MinDistSq(s.mCenter);
	return distSq <= (s.mRadius * s.mRadius);
}

bool Intersect(const Capsule& a, const Capsule& b)
{
	float distSq = LineSegment::MinDistSq(a.mSegment, b.mSegment);
	float sumRadii = a.mRadius + b.mRadius;
	return distSq <= (sumRadii * sumRadii);
}

bool Intersect(const LineSegment& l, const Plane& p, float& outT)
{
	//first test if ther's a solution for t
	float denom = Vector3::Dot(l.mEnd - l.mStart, p.mNormal);


	//denom is close to zero
	// t == 0 -> l.start intersect with plane
	if (Math::NearZero(denom))
	{
		// the only way they intersect is if start
		// is a point on the plane, (P dot N) == d
		if (Math::NearZero(Vector3::Dot(l.mStart, p.mNormal) - p.mD))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float numer = -Vector3::Dot(l.mStart, p.mNormal) - p.mD;
		outT = numer / denom;
		// validate t is within bounds of the line segment
		if (outT >= 0.0f && outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

// intersect line and sphere
bool Intersect(const LineSegment& l, const Sphere& s, float& outT)
{
	// Compute X, Y, a, b, c as per equations
	Vector3 X = l.mStart - s.mCenter;
	Vector3 Y = l.mEnd - l.mStart;
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float c = Vector3::Dot(X, X) - s.mRadius * s.mRadius;
	// compute 2nd degree equation discriminant
	float disc = b * b - 4.0f * a * c;
	if (disc < 0.0f)
	{
		return false;
	}
	else
	{
		disc = Math::Sqrt(disc);
		// compute min and max solution of t
		float tMin = (-b - disc) / (2.0f * a);
		float tMax = (-b + disc) / (2.0f * a);
		// check wheter either t is whithin bounds of segment
		if (tMin >= 0.0f && tMin <= 1.0f)
		{
			outT = tMin;
			return true;
		}
		else if (tMax >= 0.0f && tMax <= 1.0f)
		{
			outT = tMax;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TestSidePlane(float start, float end, float negd, const Vector3& norm,
	std::vector<std::pair<float, Vector3>>& out)
{
	float denom = end - start;
	if (Math::NearZero(denom))
	{
		return false;
	}
	{
		float numer = -start + negd;
		float t = numer / denom;
		//test t is with in bouds
		if (t >= 0.0f && t <= 1.0f)
		{
			out.emplace_back(t, norm);
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
//check intersect line with aabb
bool Intersect(const LineSegment& l, const AABB& b, float& outT, Vector3& outNorm)
{
	//vector to save all possible t values, and normals for thos sides
	std::vector<std::pair<float, Vector3>> tValues;
	// test the x plane
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMin.x, Vector3::NegUnitX, tValues);
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMin.x, Vector3::UnitX, tValues);
	// test the y plane
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMin.x, Vector3::NegUnitX, tValues);
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMin.x, Vector3::UnitX, tValues);
	// test the z plane
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMin.x, Vector3::NegUnitX, tValues);
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMin.x, Vector3::UnitX, tValues);

	// sort the t values in ascending order
	std::sort(tValues.begin(), tValues.end(),
		[](
			const std::pair<float, Vector3>& a,
			const std::pair<float, Vector3>& b
			) {return a.first < b.first; }
	);

	//test if the box contains any of these point of intersection
	Vector3 point;
	for (auto& t : tValues)
	{
		point = l.PointOnSegment(t.first);
		if (b.Contains(point))
		{
			// smallest t and t's vector3 are found
			outT = t.first;
			outNorm = t.second;
			return true;
		}
	}

	// None of the intersections are within bounds of box
	return false;
}

// 연속충돌감지 CCD : 이동 오브젝트가 프레임 사이 여러 점에서 충돌 판별하는 과정
// 이동중인 두 구체사이 교차(swep-sphere intersection)
bool SwepSphere(const Sphere& P0, const Sphere& P1,
	const Sphere& Q0, const Sphere& Q1, float& outT)
{
	// compute x, y, a, b, c
	Vector3 X = P0.mCenter - Q0.mCenter;
	Vector3 Y = P1.mCenter - P0.mCenter - (Q1.mCenter - Q0.mCenter);
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float sumRadii = P0.mRadius + Q0.mRadius;
	float c = Vector3::Dot(X, X) - sumRadii * sumRadii;
	//solve discriminant
	float disc = b * b - 4.0f * a * c;

	if (disc < 0.0f)
	{
		return false;
	}
	else
	{
		disc = Math::Sqrt(disc);
		//we only care about the smaller solution
		outT = (-b - disc) / (2.0f * a);
		if (outT >= 0.0f && outT <= 0.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}