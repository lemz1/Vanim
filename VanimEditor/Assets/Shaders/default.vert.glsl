#version 460 core

uniform mat4 u_ViewProjection;
uniform mat4 u_ModelMatrix;

in vec2 a_Position;
in vec2 a_TexCoord;

out vec2 o_TexCoord;

void main()
{
	gl_Position = u_ViewProjection * u_ModelMatrix * vec4(a_Position, 0.0, 1.0);

	o_TexCoord = a_TexCoord;
}
