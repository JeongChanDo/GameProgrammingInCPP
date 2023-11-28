#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/ehgith
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(
			renderer,
			mTexture, // texture to draw
			nullptr, // source rectangle 
			&r, // destination rectangle
			-Math::ToDegrees(mOwner->GetRotation()), // convert angle
			nullptr,	// point of rotation
			SDL_FLIP_NONE);
	}
}