// a simple flat colour shader
#version 410

in vec4 vColour;

out vec4 FragColour;

void main()
{
	FragColour = vec4(1, 0, 1, 1);
}