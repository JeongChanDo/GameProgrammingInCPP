#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//attrib 0 is position, 1 is normal, 2 is tex coord
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec2 fragTexCoord;

void main()
{
	//convert position to homogeneous coords
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * uWorldTransform * uViewProj;

	fragTexCoord = inTexCoord;
}