#include "MeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(Actor* owner)
	:Component(owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, mVisible(true)
{
	mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		//set the world tf
		shader->SetMatrixUniform("uWorldTransform",
			mOwner->GetWorldTrnasform());
		//set specular power
		shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
		//set the active texture
		Texture* t = mMesh->GetTexture(mTextureIndex);
		if (t)
		{
			t->SetActive();
		}
		// see the mesh's vertex array as active
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();
		//draw
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

	}
}