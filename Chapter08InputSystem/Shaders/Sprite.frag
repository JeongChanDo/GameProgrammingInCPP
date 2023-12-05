//.vert�� ���ؽ� ���̴�����
//opengl 3.3 ����
#version 330

// �����ؽ������� �Ӽ� �����ؾ���


// inPosition Ÿ���� vec3 3���� �ε��Ҽ��� ����
//in vec3 inPosition;

//���ؽ� ���̴����� ����� �����׸�Ʈ ��ǥ ������
in vec2 fragTexCoord;
// ��� ����
out vec4 outColor;
// �ý�ó ���ø��� ���
uniform sampler2D uTexture;

void main()
{
	// �ý�ó�κ��� ���� ���ø�
	outColor = texture(uTexture, fragTexCoord);
}