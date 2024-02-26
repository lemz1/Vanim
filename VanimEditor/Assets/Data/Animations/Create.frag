#version 460 core

uniform float u_Progress;
uniform vec4 u_Color;

in vec2 o_TexCoord;

out vec4 fragColor;

void main()
{
	float alpha = 1.0 - step(u_Progress, o_TexCoord.x);

	fragColor = vec4(u_Color.rgb, alpha);
}
