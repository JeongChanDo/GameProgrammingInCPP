#pragma once
class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	//update this component by delta time
	virtual void Update(float deltaTime);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	// Owning actor
	class Actor* mOwner;
	// Update order of component
	int mUpdateOrder;
};