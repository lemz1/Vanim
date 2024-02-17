#version 460 core

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

in vec3 _position;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(_position, 1.0);
}
