#include "corepch.h"
#include "Shader.h"

#include "VanimCore/Util/AssetManager.h"

namespace Vanim
{
	Shader::Shader(
		size_t count, 
		ShaderInfo* infos
	)
	:	_id(0)
	{
		_id = glCreateProgram();

		for (size_t i = 0; i < count; i++)
		{
			std::string sourceString = AssetManager::GetFileContent(infos[i].filePath);
			const char* source = sourceString.c_str();

			GLuint shaderID = glCreateShader((GLenum)infos[i].type);
			glShaderSource(shaderID, 1, &source, nullptr);
			glCompileShader(shaderID);

			glAttachShader(_id, shaderID);
			glDeleteShader(shaderID);
		}

		glLinkProgram(_id);
	}

	Shader::~Shader()
	{
		glDeleteProgram(_id);
		_id = 0;
	}

	void Shader::Bind()
	{
		glUseProgram(_id);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}
}
