#include <glut.h>

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);//���ɫ�ʻ�����
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//����
	glFlush();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//��ʼ��glut  ���ɲ�дĬ�ϣ�
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//��ʾģʽ��ʼ�� RGB��ʾģʽ��������ģʽ
	glutInitWindowPosition(100, 100);//���ڴ���λ��  ���ɲ�дĬ�ϣ�
	glutInitWindowSize(400, 400);//���ڴ�С  ���ɲ�дĬ�ϣ�
	glutCreateWindow("��һ��OpenGl����");//��������
	glutDisplayFunc(&myDisplay);//�Զ��庯����ͼ
	glutMainLoop();//��Ϣѭ����Ӧ
	return 0;
}

