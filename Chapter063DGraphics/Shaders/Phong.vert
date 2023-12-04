#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;


//세계 공간에서 법선
out vec2 fragTexCoord;
//세계공간에서 위치
out vec3 fragNormal;
out vec3 fragWorldPos;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);

	pos = pos * uWorldTransform;
	// 세계 공간상 위치 저장
	fragWorldPos = pos.xyz;
	// 위치 클립 공간으로 변환
	gl_Position = pos * uViewProj;

	// 법선을 세계공간상의 법선으로 변환 (w=0)
	fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

	//택스처 좌표를 프레그먼트 세이더로 전달
	fragTexCoord = inTexCoord;

}