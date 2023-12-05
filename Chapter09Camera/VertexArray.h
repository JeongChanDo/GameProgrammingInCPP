#pragma once
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVErts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	// how many vertices in the vertex buffer
	unsigned int mNumVerts;
	// how many indices in the index buffer
	unsigned int mNumIndices;
	// opengl id of the vertex buffer
	unsigned int mVertexBuffer;
	// opengl id of the index buffer
	unsigned int mIndexBuffer;
	// opengl id of the vertex array object
	unsigned int mVertexArray;
};