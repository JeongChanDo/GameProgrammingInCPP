#pragma once
#include <GL/glew.h>

#include <string>
#include "Math.h"

/*
c++에서 쉐이더 파일로드해서 opengl이 인식하도록해야함
1. 버텍스 쉐이더 로드, 컴파일
2. 픽셀 쉐이더 로드, 컴파일
3. 두 쉐이더를 쉐이더 프로그램에 연결
*/

class Shader
{
public:
	Shader();
	~Shader();
	
	bool Load(const std::string& bertName, const std::string& fragName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	/*
	1. 컴파일 할 세이더 파일 이름
	2. 세이더 타입
	3. ID 저장할 참조 파라미터
	*/
	bool CompileShader(
		const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader
	);
	//성공적으로 세이더 컴파일됬는지 체크
	bool isCompiled(GLuint shader);
	// 버텍스/정점 프로그램이 연결되었는지 체크
	bool isValidProgram();
private:
	//세이더 오브젝트의 id 저장
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};