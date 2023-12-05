#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// create vertex array
	// opengl�� �����ʹ�� ������ id ���, 1�� ����
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
	
	// create vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER,				//�����͸� �� ������ ���� Ÿ��
		//numVerts * 3 * sizeof(float),	//������ ����Ʈ ũ�� ���� �ﰢ���Ҷ� ������
		numVerts * 5 * sizeof(float),	//������ ����Ʈ ũ��
		verts,							// ������ �ҽ�(������)
		GL_STATIC_DRAW					// ������ ��� �뵵
	);

	// create index buffer
	// ID�� ���� ��ü���� �������� �ʾ� ���ؽ� ����, �ε��� ���۰� 1�� ���Ƶ� ����
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			//�ε��� ���۷� ���۸� ���
		numIndices * sizeof(unsigned int),	//ũ��
		indices, GL_STATIC_DRAW
	);

	//specify the vertex attribute
	// ��ġ ���ؽ� �Ӽ��� �ٷ�
	glEnableVertexAttribArray(0); // ù ���ؽ� �Ӽ� Ȱ��ȭ �ε����� 0
	glVertexAttribPointer(
		0,					// �Ӽ� �ε��� (ù ���ؽ� �Ӽ� �ε����� 0 �̹Ƿ�)
		3,					// ��� �� 3 (x, y, z 3���̹Ƿ�)
		GL_FLOAT,			// ��� Ÿ��
		GL_FALSE,			// ���������� ���
		//sizeof(float) * 3,	// ����(�� ���ؽ� ũ��) - ���ؽ� ���� ����Ʈ ������
		sizeof(float) * 5,	// ����(�� ���ؽ� ũ��) - ���ؽ� ���� ����Ʈ ������
		0					// ���ؽ� ���ۿ��� �̼Ӽ����� ������ - ���ؽ� ������ġ�� �����ϹǷ� 0
	);

	// �ؽ�ó ��ǥ �Ӽ��� �����ϱ����� ���ؽ� �Ӽ� 1 Ȱ��ȭ�Ͽ� ����
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,					//���ؽ� �Ӽ� �ε���
		2,					// ������Ʈ�� �� uv, 2
		GL_FLOAT,			// ������Ʈ Ÿ��
		GL_FALSE,
		sizeof(float) * 5,	//���� (�׻� ���ؽ� ũ��)
		reinterpret_cast<void*>(sizeof(float) * 3)	//������ ������
	);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteBuffers(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	// ����� ���ؽ� �迭 ����
	glBindVertexArray(mVertexArray);
}