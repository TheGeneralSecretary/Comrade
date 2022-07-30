#version 460 core

out vec4 o_Color;

in vec4 v_Color;

void main()
{
	o_Color = vec4(v_Color);
}
