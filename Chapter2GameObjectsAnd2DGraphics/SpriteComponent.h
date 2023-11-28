#pragma once
#include "Component.h"
#include "SDL.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }


protected:
	// Texture to draw
	SDL_Texture* mTexture;
	//Draw order used for painter's algorithm
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};