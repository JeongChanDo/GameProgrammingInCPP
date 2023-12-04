#pragma once
#include <vector>
#include <string>

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
	// get specular power of mesh
	float GetSpecPower() const { return mSpecPower; }
private:
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