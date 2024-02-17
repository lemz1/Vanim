#version 460 core

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

in vec2 a_Position;

out vec2 o_TexCoord;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 0.0, 1.0);

	o_TexCoord = a_Position; // change this in the future
}
