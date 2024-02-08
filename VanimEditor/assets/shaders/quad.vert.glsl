#version 460 core

uniform mat4 u_ModelViewProjection;

out vec2 o_TextureCoord;

void main() 
{
	int x = int(floor(gl_VertexID / 2));
	int y = int(mod(gl_VertexID, 2));
	
	float posX = float(x) - 0.5;
	float posY = float(y) - 0.5;

	gl_Position = u_ModelViewProjection * vec4(posX, posY, 0.0, 1.0);

	o_TextureCoord = vec2(mod(x, 2), mod(y, 2));
}
