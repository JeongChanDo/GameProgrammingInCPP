#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	void Update(float deltaTime) override;
	void SetAnimTexture(const std::vector<SDL_Texture*>& texture);
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

public:
	std::vector<SDL_Texture*> mAnimTextures;
	float mCurrFrame;
	float mAnimFPS;
};