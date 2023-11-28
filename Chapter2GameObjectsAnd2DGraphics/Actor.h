#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	// Constructor/destructor
	Actor(class Game* game);
	virtual ~Actor();

	//update function called from game (not overridable)
	void Update(float deltaTime);
	// update all the components attached to the actor(not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	//Getters/Setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SEtRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	class Game* GetGame() { return mGame; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState;
	// tf
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// compoents held by this actor
	std::vector<class Component*> mComponents;
	class Game* mGame;
};