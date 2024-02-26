#pragma once

#include "VanimCore/Base.h"

#include <stdint.h>
#include <glad/glad.h>

namespace Vanim
{
	enum class ShaderType : GLenum
	{
		VertexShader = GL_VERTEX_SHADER,
		FragmentShader = GL_FRAGMENT_SHADER,
		ComputeShader = GL_COMPUTE_SHADER,
	};

	struct ShaderInfo
	{
		const char* filePath;
		ShaderType type;
	};

	class Shader
	{
	public:
		Shader() = default;
		Shader(
			size_t count,
			ShaderInfo* infos
		);
		~Shader();

		void Bind() const;
		void Unbind() const;

		GLint GetUniformLocation(const char* variable) const
		{
			return glGetUniformLocation(_id, variable);
		}

		void SetFloat(
			GLint location,
			GLfloat v0
		) const
		{
			glUniform1f(location, v0);
		}

		void SetFloats(
			GLint location,
			GLfloat v0,
			GLfloat v1
		) const
		{
			glUniform2f(location, v0, v1);
		}

		void SetFloats(
			GLint location,
			GLfloat v0,
			GLfloat v1,
			GLfloat v2
		) const
		{
			glUniform3f(location, v0, v1, v2);
		}

		void SetFloats(
			GLint location,
			GLfloat v0,
			GLfloat v1,
			GLfloat v2,
			GLfloat v3
		) const
		{
			glUniform4f(location, v0, v1, v2, v3);
		}

		void SetDouble(
			GLint location,
			GLdouble v0
		) const
		{
			glUniform1d(location, v0);
		}

		void SetDoubles(
			GLint location,
			GLdouble v0,
			GLdouble v1
		) const
		{
			glUniform2d(location, v0, v1);
		}

		void SetDoubles(
			GLint location,
			GLdouble v0,
			GLdouble v1,
			GLdouble v2
		) const
		{
			glUniform3d(location, v0, v1, v2);
		}

		void SetDoubles(
			GLint location,
			GLdouble v0,
			GLdouble v1,
			GLdouble v2,
			GLdouble v3
		) const
		{
			glUniform4d(location, v0, v1, v2, v3);
		}

		void SetInt(
			GLint location,
			GLint v0
		) const
		{
			glUniform1i(location, v0);
		}

		void SetInts(
			GLint location,
			GLint v0,
			GLint v1
		) const
		{
			glUniform2i(location, v0, v1);
		}

		void SetInts(
			GLint location,
			GLint v0,
			GLint v1,
			GLint v2
		) const
		{
			glUniform3i(location, v0, v1, v2);
		}

		void SetInts(
			GLint location,
			GLint v0,
			GLint v1,
			GLint v2,
			GLint v3
		) const
		{
			glUniform4i(location, v0, v1, v2, v3);
		}

		void SetUInt(
			GLint location,
			GLuint v0
		) const
		{
			glUniform1ui(location, v0);
		}

		void SetUInts(
			GLint location,
			GLuint v0,
			GLuint v1
		) const
		{
			glUniform2ui(location, v0, v1);
		}

		void SetUInts(
			GLint location,
			GLuint v0,
			GLuint v1,
			GLuint v2
		) const
		{
			glUniform3ui(location, v0, v1, v2);
		}

		void SetUInts(
			GLint location,
			GLuint v0,
			GLuint v1,
			GLuint v2,
			GLuint v3
		) const
		{
			glUniform4ui(location, v0, v1, v2, v3);
		}

		void SetFloatArray(
			GLint location,
			GLsizei count,
			const GLfloat* value
		) const
		{
			glUniform1fv(location, count, value);
		}

		void SetVec2Array(
			GLint location,
			GLsizei count,
			const GLfloat* value
		) const
		{
			glUniform2fv(location, count, value);
		}

		void SetVec3Array(
			GLint location,
			GLsizei count,
			const GLfloat* value
		) const
		{
			glUniform3fv(location, count, value);
		}

		void SetVec4Array(
			GLint location,
			GLsizei count,
			const GLfloat* value
		) const
		{
			glUniform4fv(location, count, value);
		}

		void SetDoubleArray(
			GLint location,
			GLsizei count,
			const GLdouble* value
		) const
		{
			glUniform1dv(location, count, value);
		}

		void SetDoubleVec2Array(
			GLint location,
			GLsizei count,
			const GLdouble* value
		) const
		{
			glUniform2dv(location, count, value);
		}

		void SetDoubleVec3Array(
			GLint location,
			GLsizei count,
			const GLdouble* value
		) const
		{
			glUniform3dv(location, count, value);
		}

		void SetDoubleVec4Array(
			GLint location,
			GLsizei count,
			const GLdouble* value
		) const
		{
			glUniform4dv(location, count, value);
		}

		void SetIntArray(
			GLint location,
			GLsizei count,
			const GLint* value
		) const
		{
			glUniform1iv(location, count, value);
		}

		void SetIntVec2Array(
			GLint location,
			GLsizei count,
			const GLint* value
		) const
		{
			glUniform2iv(location, count, value);
		}

		void SetIntVec3Array(
			GLint location,
			GLsizei count,
			const GLint* value
		) const
		{
			glUniform3iv(location, count, value);
		}

		void SetIntVec4Array(
			GLint location,
			GLsizei count,
			const GLint* value
		) const
		{
			glUniform4iv(location, count, value);
		}

		void SetUIntArray(
			GLint location,
			GLsizei count,
			const GLuint* value
		) const
		{
			glUniform1uiv(location, count, value);
		}

		void SetUIntVec2Array(
			GLint location,
			GLsizei count,
			const GLuint* value
		) const
		{
			glUniform2uiv(location, count, value);
		}

		void SetUIntVec3Array(
			GLint location,
			GLsizei count,
			const GLuint* value
		) const
		{
			glUniform3uiv(location, count, value);
		}

		void SetUIntVec4Array(
			GLint location,
			GLsizei count,
			const GLuint* value
		) const
		{
			glUniform4uiv(location, count, value);
		}

		void Set2x2Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix2fv(location, count, transpose, value);
		}

		void Set3x3Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix3fv(location, count, transpose, value);
		}

		void Set4x4Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix4fv(location, count, transpose, value);
		}

		void Set2x3Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix2x3fv(location, count, transpose, value);
		}

		void Set3x2Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix3x2fv(location, count, transpose, value);
		}

		void Set2x4Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix2x4fv(location, count, transpose, value);
		}

		void Set4x2Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix4x2fv(location, count, transpose, value);
		}

		void Set3x4Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix3x4fv(location, count, transpose, value);
		}

		void Set4x3Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLfloat* value
		) const
		{
			glUniformMatrix4x3fv(location, count, transpose, value);
		}

		void SetDouble2x2Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix2dv(location, count, transpose, value);
		}

		void SetDouble3x3Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix3dv(location, count, transpose, value);
		}

		void SetDouble4x4Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix4dv(location, count, transpose, value);
		}

		void SetDouble2x3Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix2x3dv(location, count, transpose, value);
		}

		void SetDouble3x2Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix3x2dv(location, count, transpose, value);
		}

		void SetDouble2x4Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix2x4dv(location, count, transpose, value);
		}

		void SetDouble4x2Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix4x2dv(location, count, transpose, value);
		}

		void SetDouble3x4Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix3x4dv(location, count, transpose, value);
		}

		void SetDouble4x3Matrix(
			GLint location,
			GLsizei count,
			GLboolean transpose,
			const GLdouble* value
		) const
		{
			glUniformMatrix4x3dv(location, count, transpose, value);
		}
	private:
		GLuint _id;
	};
}
