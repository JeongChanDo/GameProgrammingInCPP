#include "PhysWorld.h"
#include <algorithm>
#include "BoxComponent.h"
#include <SDL.h>

PhysWorld::PhysWorld(Game* game)
	:mGame(game)
{

}

bool PhysWorld::SegmentCast(const LineSegment& l, CollisionInfo& outColl)
{
	bool collided = false;
	//init closestT to infinity
	// first intersection will always update closestT
	float closestT = Math::Infinity;
	//variable to save intersection vector
	Vector3 norm;
	// test against all box
	for (auto box : mBoxes)
	{
		//variable to save intersection time
		float t;
		// does the line segment intersect with the box?
		if (Intersect(l, box->GetWorldBox(), t, norm))
		{
			// is the closer than previous intersection?
			if (t < closestT)
			{
				closestT = t;
				outColl.mPoint = l.PointOnSegment(t);
				outColl.mNormal = norm;
				outColl.mBox = box;
				outColl.mActor = box->GetOwner();
				collided = true;
			}
		}
	}
	return collided;
}

// Naive implementation O(n^2)
void PhysWorld::TestPairwise(std::function<void(Actor*, Actor*)> f)
{
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// Don't need to test vs itself and any previous i values
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxComponent* a = mBoxes[i];
			BoxComponent* b = mBoxes[j];
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				// Call supplied function to handle intersection
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::TestSweepAndPrune(std::function<void(Actor*, Actor*)> f)
{
	// Sort by min.x
	std::sort(mBoxes.begin(), mBoxes.end(),
		[](BoxComponent* a, BoxComponent* b) {
			return a->GetWorldBox().mMin.x <
				b->GetWorldBox().mMin.x;
		});
	
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// get for box[i]'s max.x
		BoxComponent* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxComponent* b = mBoxes[j];
			// if box[j] min.x is over box[i].max.x
			// there are no collisions woth box[i]
			if ( b->GetWorldBox().mMin.x > max)
			{
				break;
			} 
			else if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::AddBox(BoxComponent* box)
{
	mBoxes.emplace_back(box);
}

void PhysWorld::RemoveBox(BoxComponent* box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end())
	{
		//swap to end of vector and pop off
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}
}