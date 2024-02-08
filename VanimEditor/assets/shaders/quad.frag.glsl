#version 460 core

uniform vec4 u_Color;

in vec2 o_TextureCoord;

out vec4 fragColor;

void main() 
{
	fragColor = vec4(u_Color.xy * o_TextureCoord.xy, u_Color.za);
}
