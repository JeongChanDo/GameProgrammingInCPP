//.vert는 버텍스 쉐이더파일
//opengl 3.3 버전
#version 330

// 각버텍스에대한 속성 지정해야함


// inPosition 타입은 vec3 3개의 부동소수점 벡터
in vec3 inPosition;

void main()
{
	//x, y, z에다 w요소를 1.0으로 추가해서 gl_Position에 저장
	gl_Position = vec4(inPosition, 1.0);
}