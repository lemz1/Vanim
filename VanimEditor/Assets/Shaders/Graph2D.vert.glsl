#version 460 core

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

// x = left, y = right, z = bottom, w = top
uniform vec4 u_Bounds;

in vec2 a_Position;

out vec2 o_TexCoord;

float inverseLerp(float a, float b, float value) 
{
    if (a != b) 
    {
        return (value - a) / (b - a);
    } 
    else 
    {
        // Avoid division by zero
        return 0.0;
    }
}

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 0.0, 1.0);

	o_TexCoord = vec2(
        inverseLerp(u_Bounds.x, u_Bounds.y, a_Position.x),
        inverseLerp(u_Bounds.z, u_Bounds.w, a_Position.y)
    );
}
