#include "corepch.h"
#include "Renderer.h"

namespace Vanim
{
	void Renderer::DrawMesh(
		const Shared<Shader>& shader,
		const Shared<VertexArray>& vao, 
		GLsizei numIndices
	)
	{
		shader->Bind();
		vao->Bind();

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

		vao->Unbind();
		shader->Unbind();
	}
}
