#version 460 core

in vec2 o_TextureCoord;

out vec4 fragColor;

void main() 
{
	fragColor = vec4(o_TextureCoord, 0.0, 1.0);
}
