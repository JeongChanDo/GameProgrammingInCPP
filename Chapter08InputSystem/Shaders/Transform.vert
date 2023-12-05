//.vert�� ���ؽ� ���̴�����
//opengl 3.3 ����
#version 330

// �����ؽ������� �Ӽ� �����ؾ���


// uniform ����ϸ� ��� �����ϰ� ������, in out�� ���̴� ���ට���ٹٲ�
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// inPosition Ÿ���� vec3 3���� �ε��Ҽ��� ����
in vec3 inPosition;

void main()
{
	//x, y, z���� w��Ҹ� 1.0���� �߰��ؼ� gl_Position�� ����
	vec4 pos = vec4(inPosition, 1.0);
	// v' = v * worldtf_mat * simpleviewproj_mat
	gl_Position = pos * uWorldTransform * uViewProj;
}