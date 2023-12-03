#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
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


void SpriteComponent::Draw(Shader* shader)
{
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(mTexWidth),
		static_cast<float>(mTexHeight),
		1.0f
	);

	Matrix4 world = scaleMat * mOwner->GetWorldTranform();
	//셰계 변환 행렬 설정
	shader->SetMatrixUniform("uWorldTransform", world);
	//mTexture->SetActive();

	glDrawElements(
		GL_TRIANGLES,	//그려야할 폴리곤 수
		6,				//인덱스 버퍼에 있는 인덱스 수
		GL_UNSIGNED_INT,//각인덱스 타입
		nullptr
	);
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}