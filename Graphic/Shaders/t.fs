#version 330 core

// Interpolated values from the vertex shaders
uniform sampler2D colorTexture;

in vec2 fragTexcoord;
in vec3 testPos;

// Ouput data
out vec4 color;

void main()
{

//	color = vec4(fragTexcoord.x,fragTexcoord.y,0,1);
	
//	color = vec4(testPos.x,testPos.y, testPos.z,1);
	color = texture(colorTexture, fragTexcoord);
//	color = vec4(1, 0, 0, 1);
}
