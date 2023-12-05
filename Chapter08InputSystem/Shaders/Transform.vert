//.vert는 버텍스 쉐이더파일
//opengl 3.3 버전
#version 330

// 각버텍스에대한 속성 지정해야함


// uniform 사용하면 계속 동일하게 유지됨, in out은 셰이더 실행때마다바뀜
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// inPosition 타입은 vec3 3개의 부동소수점 벡터
in vec3 inPosition;

void main()
{
	//x, y, z에다 w요소를 1.0으로 추가해서 gl_Position에 저장
	vec4 pos = vec4(inPosition, 1.0);
	// v' = v * worldtf_mat * simpleviewproj_mat
	gl_Position = pos * uWorldTransform * uViewProj;
}