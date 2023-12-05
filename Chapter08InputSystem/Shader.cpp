#include "Shader.h"
#include "Texture.h"
#include <SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader()
	:mShaderProgram(0)
	, mVertexShader(0)
	, mFragShader(0)
{

}

Shader::~Shader()
{

}

bool Shader::CompileShader(const std::string& fileName,
	GLenum shaderType,
	GLuint& outShader)
{
	// open file
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		//read all text into a string
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// ���� Ÿ�� ���̴� ����
		outShader = glCreateShader(shaderType);
		// src ���ڿ� �����ϰ�, ������ �õ�
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!isCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

bool Shader::isCompiled(GLuint shader)
{
	GLint status;
	// ������ ���� Ȯ��
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	if 
	(
		!CompileShader
		(
			vertName,
			GL_VERTEX_SHADER,
			mVertexShader) ||
		!CompileShader
		(
			fragName,
			GL_FRAGMENT_SHADER,
			mFragShader
		)
	)
	{
		return false;
	}

	// ���ؽ�/�ȼ� ���̴� �����ϴ� ���̴����α׷� ����
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	// �� ����Ǿ����� ����
	if (!isValidProgram())
	{
		return false;
	}
	return true;
}

bool Shader::isValidProgram()
{
	GLint status;
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
	// ���α׷��� Ȱ�����·� ����
	glUseProgram(mShaderProgram);
}

// world tf, view-proj mat�� ���Ǵ� uniform ���� ����
void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	// �ش� �̸��� uniform ã��
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// ��� �����͸� uniform���� ����
	glUniformMatrix4fv(
		loc,		//uniform ID
		1,			// num of mat
		GL_TRUE,	//�຤�� ���� true
		matrix.GetAsFloatPtr()	// ��ĵ����Ϳ����� ������
	);
}