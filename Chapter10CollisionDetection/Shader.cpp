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

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	// compile vertex and pixel shader
	if (
		!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
		!CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader)
		)
	{
		return false;
	}

	//now create a shader program
	// that links together the vertx/frag shaders
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	if (!IsValidProgram())
	{
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
	glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	//find the uniform by tis name
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// send matrix data to the uniform
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetVectorUniform(const char* name, const Vector3& vector)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	glUniform3fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char* name, float value)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	glUniform1f(loc, value);
}


bool Shader::CompileShader(const std::string& fileName,
	GLenum shaderType,
	GLuint& outShader)
{
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		//create a shader of specified type
		outShader = glCreateShader(shaderType);
		// set the source character and try to compile
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
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

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	// query the compile status
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

bool Shader::IsValidProgram()
{
	GLint status;
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL LInk Status:\n%s", buffer);
		return false;
	}
	return true;
}