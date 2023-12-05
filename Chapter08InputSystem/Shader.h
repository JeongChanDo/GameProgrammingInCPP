#pragma once
#include <GL/glew.h>

#include <string>
#include "Math.h"

/*
c++���� ���̴� ���Ϸε��ؼ� opengl�� �ν��ϵ����ؾ���
1. ���ؽ� ���̴� �ε�, ������
2. �ȼ� ���̴� �ε�, ������
3. �� ���̴��� ���̴� ���α׷��� ����
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
	1. ������ �� ���̴� ���� �̸�
	2. ���̴� Ÿ��
	3. ID ������ ���� �Ķ����
	*/
	bool CompileShader(
		const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader
	);
	//���������� ���̴� �����ω���� üũ
	bool isCompiled(GLuint shader);
	// ���ؽ�/���� ���α׷��� ����Ǿ����� üũ
	bool isValidProgram();
private:
	//���̴� ������Ʈ�� id ����
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};