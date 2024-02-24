#version 460 core

uniform vec4 u_Color;

in vec2 o_TexCoord;

out vec4 fragColor;

void main()
{
	fragColor = u_Color;
}
