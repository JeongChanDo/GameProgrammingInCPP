//.vert�� ���ؽ� ���̴�����
//opengl 3.3 ����
#version 330

// �����ؽ������� �Ӽ� �����ؾ���


// inPosition Ÿ���� vec3 3���� �ε��Ҽ��� ����
in vec3 inPosition;

void main()
{
	//x, y, z���� w��Ҹ� 1.0���� �߰��ؼ� gl_Position�� ����
	gl_Position = vec4(inPosition, 1.0);
}