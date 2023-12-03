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

		// 지정 타입 세이더 생성
		outShader = glCreateShader(shaderType);
		// src 문자열 설정하고, 컴파일 시도
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
	// 컴파일 상태 확인
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

	// 버텍스/픽셀 세이더 연결하는 세이더프로그램 생성
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	// 잘 연결되었는지 검증
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
	// 프로그램을 활성상태로 설정
	glUseProgram(mShaderProgram);
}

// world tf, view-proj mat에 사용되는 uniform 변수 설정
void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	// 해당 이름의 uniform 찾음
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// 행렬 데이터를 uniform으로 전송
	glUniformMatrix4fv(
		loc,		//uniform ID
		1,			// num of mat
		GL_TRUE,	//행벡터 쓰면 true
		matrix.GetAsFloatPtr()	// 행렬데이터에대한 포인터
	);
}