#pragma once
#include <vector>
#include <string>
#include "Collision.h"
class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	//get vertex array associated with the mesh
	class VertexArray* GetVertexArray() { return mVertexArray; }
	// get a texture from specified index
	class Texture* GetTexture(size_t index);
	//get name of shader
	const std::string& GetShaderName() const { return mShaderName; }
	//get object space bounding sphere radius
	float GetRadius() const { return mRadius; }
	// get object space bounding box
	const AABB& GetBox() const { return mBox; }
	// get specular power of mesh
	float GetSpecPower() const { return mSpecPower; }
private:
	//AABB collision
	AABB mBox;
	//textures associated with this mesh
	std::vector<class Texture*> mTextures;
	// vectex array associated with this mesh
	class VertexArray* mVertexArray;
	// Name of shader spedcified by mesh
	std::string mShaderName;
	// stores object space bounding sphere radius
	float mRadius;
	// specular power of surface
	float mSpecPower;
};