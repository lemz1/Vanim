#include "vanimpch.h"
#include "Transform.h"

namespace Vanim
{
	Transform::Transform(
		const glm::vec3& position, 
		const glm::quat& rotation, 
		const glm::vec3& scale
	)
		: _position(position),
		_rotation(rotation),
		_scale(scale)
	{
		RecalculateMatrix();
	}

	void Transform::RecalculateMatrix()
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f), _position);
		glm::mat4 rotationMatrix = glm::mat4_cast(_rotation);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), _scale);

		_matrix = translationMatrix * rotationMatrix * scaleMatrix;
	}
}
