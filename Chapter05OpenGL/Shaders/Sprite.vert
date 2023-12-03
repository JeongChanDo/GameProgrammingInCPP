//.vert�� ���ؽ� ���̴�����
//opengl 3.3 ����
#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//����
// �����ؽ������� �Ӽ� �����ؾ���
// inPosition Ÿ���� vec3 3���� �ε��Ҽ��� ����
//in vec3 inPosition;


// �������� ���ؽ� �Ӽ��� �ϳ����̶� ������ ��ġ�ϳ��� ����
//������ �Ӽ��� 2���Ƿ� � �Ӽ��� � �������� �����ؾ���
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;

// �����׸�Ʈ ���̴��� �ؽ�ó ��ǥ �ʿ��ϹǷ� out ���� ����
out vec2 fragTexCoord;


void main()
{
	//x, y, z���� w��Ҹ� 1.0���� �߰��ؼ� gl_Position�� ����
	vec4 pos = vec4(inPosition, 1.0);

	// ��ġ�� ���� �������� ���� �� Ŭ�� �������� ��ȯ
	gl_Position = pos * uWorldTransform * uViewProj;
	// �ؽ�ó ��ǥ�� �����׸�Ʈ(�ȼ�)���̴��� ����
	fragTexCoord = inTexCoord;

}