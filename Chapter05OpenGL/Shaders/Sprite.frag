//.vert는 버텍스 쉐이더파일
//opengl 3.3 버전
#version 330

// 각버텍스에대한 속성 지정해야함


// inPosition 타입은 vec3 3개의 부동소수점 벡터
//in vec3 inPosition;

//버텍스 셰이더에서 출력한 프레그먼트 좌표 가져옴
in vec2 fragTexCoord;
// 출력 색상
out vec4 outColor;
// 택스처 샘플링에 사용
uniform sampler2D uTexture;

void main()
{
	// 택스처로부터 색상 샘플링
	outColor = texture(uTexture, fragTexCoord);
}