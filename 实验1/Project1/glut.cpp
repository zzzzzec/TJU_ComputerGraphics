#include <glut.h>

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);//清空色彩缓存区
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//绘制
	glFlush();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//初始化glut  （可不写默认）
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//显示模式初始化 RGB显示模式，单缓冲模式
	glutInitWindowPosition(100, 100);//窗口窗口位置  （可不写默认）
	glutInitWindowSize(400, 400);//窗口大小  （可不写默认）
	glutCreateWindow("第一个OpenGl程序");//窗口名称
	glutDisplayFunc(&myDisplay);//自定义函数绘图
	glutMainLoop();//消息循环相应
	return 0;
}

