#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Vanim
{
	struct Transform
	{
	public:
		Transform(
			const glm::vec3& position = glm::vec3(0),
			const glm::quat& rotation = glm::quat(glm::radians(glm::vec3(0))),
			const glm::vec3& scale	= glm::vec3(1)
		);

		const glm::vec3& GetPosition() const { return _position; }
		const glm::quat& GetRotation() const { return _rotation; }
		const glm::vec3& GetScale() const { return _scale; }
		const glm::mat4& AsMat4() const { return _matrix; }
	private:
		void RecalculateMatrix();
	private:
		glm::vec3	_position;
		glm::quat	_rotation;
		glm::vec3	_scale;

		glm::mat4	_matrix;
	};
}
