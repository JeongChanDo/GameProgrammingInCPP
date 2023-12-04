#version 330

in vec2 fragTexCoord;

// this corresponds to the output color to the color buffer
out vec4 outColor;

// this is used for texture sampling
uniform sampler2D uTexture;

void main()
{
	//sample color fram texture
	outColor = texture(uTexture, fragTexCoord);
}