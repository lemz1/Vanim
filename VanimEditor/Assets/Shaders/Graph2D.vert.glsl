#version 460 core

in vec2 _position;

void main()
{
	gl_Position = vec4(_position, 0.0, 1.0);
}
