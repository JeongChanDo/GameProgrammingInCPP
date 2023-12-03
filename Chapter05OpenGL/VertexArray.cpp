#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// create vertex array
	// opengl은 포인터대신 정수형 id 사용, 1로 지정
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
	
	// create vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER,				//데이터를 쓸 버퍼의 버퍼 타입
		//numVerts * 3 * sizeof(float),	//복사할 바이트 크기 이전 삼각형할때 쓰던거
		numVerts * 5 * sizeof(float),	//복사할 바이트 크기
		verts,							// 복사할 소스(포인터)
		GL_STATIC_DRAW					// 데이터 사용 용도
	);

	// create index buffer
	// ID는 여러 개체마다 고유하지 않아 버텍스 버퍼, 인덱스 버퍼가 1로 같아도 가능
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			//인덱스 버퍼로 버퍼를 사용
		numIndices * sizeof(unsigned int),	//크기
		indices, GL_STATIC_DRAW
	);

	//specify the vertex attribute
	// 위치 버텍스 속성만 다룸
	glEnableVertexAttribArray(0); // 첫 버텍스 속성 활성화 인덱스는 0
	glVertexAttribPointer(
		0,					// 속성 인덱스 (첫 버텍스 속성 인덱스는 0 이므로)
		3,					// 요소 수 3 (x, y, z 3개이므로)
		GL_FLOAT,			// 요소 타입
		GL_FALSE,			// 정수에서만 사용
		//sizeof(float) * 3,	// 간격(각 버텍스 크기) - 버텍스 사이 바이트 오프셋
		sizeof(float) * 5,	// 간격(각 버텍스 크기) - 버텍스 사이 바이트 오프셋
		0					// 버텍스 시작에서 이속성까지 오프셋 - 버텍스 시작위치와 동일하므로 0
	);

	// 텍스처 좌표 속성을 설정하기위해 버텍스 속성 1 활성화하여 지정
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,					//버텍스 속성 인덱스
		2,					// 컴포넌트의 수 uv, 2
		GL_FLOAT,			// 컴포넌트 타입
		GL_FALSE,
		sizeof(float) * 5,	//간격 (항상 버텍스 크기)
		reinterpret_cast<void*>(sizeof(float) * 3)	//오프셋 포인터
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
	// 사용할 버텍스 배열 지정
	glBindVertexArray(mVertexArray);
}