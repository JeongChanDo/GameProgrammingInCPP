// .frag 프래그먼트(픽셀) 쉐이더파일
#version 330

//최종 색상 outColor에
out vec4 outColor;

void main()
{
	//RGBA 100퍼 블루, 100퍼 불투명
	outColor = vec4(0.0, 0.0, 1.0, 1.0);
}