#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
	Vector3 mDirection;
	Vector3 mDiffuseColor;
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize(float screenWidth, float screenheight);
	void Shutdown();
	void UnloadData();
	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);
	
	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);

	void SetViewMatrix(const Matrix4& view) { mView = view; }

	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	//given a screen space point, unprojects it into world
	// based on the current 3d view/projection matrices
	//expected ranges:
	// x = [-screenWidth/2, + screenWidth/2]
	// y = [-screenHeight/2, +screenHeight/2]
	// z = [0, 1 -- 0 is closer to cam, 1 is futher
	Vector3 Unproject(const Vector3& screenPoint) const;
	void GetScreenDirection(Vector3& outStart, Vector3& outDir) const;

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader);

	// map of textures loaded
	std::unordered_map<std::string, class Texture*> mTextures;
	//Map of meshes loaded
	std::unordered_map<std::string, class Mesh*> mMeshs;

	// map of meshsloaded
	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class MeshComponent*> mMeshComps;

	class Game* mGame;
	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
	class Shader* mMeshShader;

	// vie/projection for 3dshaders
	Matrix4 mView;
	Matrix4 mProjection;
	float mScreenWidth;
	float mScreenHeight;

	//lighting data
	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	SDL_Window* mWindow;
	SDL_GLContext mContext;

};