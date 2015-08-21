#version 330 core

// Interpolated values from the vertex shaders
uniform sampler2D colorTexture;

uniform vec2 textSize;

in vec2 fragTexcoord;

// Ouput data
out vec4 color;

void main()
{
	//color = texture(colorTexture, fragTexcoord + (0.5f / textSize));
	color = texture(colorTexture, fragTexcoord);
}
