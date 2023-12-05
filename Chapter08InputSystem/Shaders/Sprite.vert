//.vert는 버텍스 쉐이더파일
//opengl 3.3 버전
#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//이전
// 각버텍스에대한 속성 지정해야함
// inPosition 타입은 vec3 3개의 부동소수점 벡터
//in vec3 inPosition;


// 이전에는 버텍스 속성이 하나뿐이라 변수로 위치하나만 선언
//지금은 속성이 2개므로 어떤 속성이 어떤 변수인지 지정해야함
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;

// 프레그먼트 셰이더도 텍스처 좌표 필요하므로 out 으로 선언
out vec2 fragTexCoord;


void main()
{
	//x, y, z에다 w요소를 1.0으로 추가해서 gl_Position에 저장
	vec4 pos = vec4(inPosition, 1.0);

	// 위치를 세게 공간으로 변한 뒤 클립 공간으로 변환
	gl_Position = pos * uWorldTransform * uViewProj;
	// 텍스처 좌표를 프레그먼트(픽셀)세이더로 전달
	fragTexCoord = inTexCoord;

}