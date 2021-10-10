#include "common.h"
//#define DDA
#define BERSENHAM
static void myDDA_template(int x0, int y0, int x1, int y1,int color);
static void Bersenham_template(int x0, int y0, int x1, int y1);
static void Bersenham_template_1(int dx, int dy, int x, int y, int degree);


void draw_pixel_virtual(int x, int y, int color) {
	draw_pixel_real(TO_REAL_PIXEL(x), TO_REAL_PIXEL(y), color);
}

void draw_pixel_real(int x, int y, int color) {
#ifdef DEBUG
	printf("Draw_Pixel(%d , %d)\n", x, y);
#endif // DEBUG
	switch (color)
	{
	case red:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case blue:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case yellow:
		glColor3f(1.0, 1.0, 0.0);
		break;
	case white:
		glColor3f(1.0, 1.0, 1.0);
		break;
	default:
		glColor3f(0.0, 0.0, 0.0);
		break;
	}

	glPointSize(1);
	glBegin(GL_POINTS);
	for (int i = 0; i < PIXEL; i++) {
		for (int j = 0; j < PIXEL; j++) {
			glVertex2i(x + i, y + j);
		}
	}
	glEnd();
}

void draw_grid(int width , int heigh){
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (int x = 0; x < width; x = x + PIXEL) {
		for (int y = 0; y < heigh; y++) {
			glVertex2i(x, y);
		}
	}
	for (int y = 0; y < heigh; y = y + PIXEL) {
		for (int x = 0; x < width; x++) {
			glVertex2i(x, y);
		}
	}
	glEnd();
}

void myDDA(Point start , Point end, int color) {
	myDDA_template(TO_VIRTUAL_PIXEL(start.x), TO_VIRTUAL_PIXEL(start.y), TO_VIRTUAL_PIXEL(end.x), TO_VIRTUAL_PIXEL(end.y),color);
}

static void myDDA_template(int x0, int y0, int x1, int y1, int color) {
	//这里都使用虚拟坐标进行计算
	//printf("%d %d %d %d \n", x0, y0, x1, y1);
	draw_pixel_virtual(x0, y0 ,DEFAULT_COLOR);
	float x = x0, y = y0;
	float dx = x1 - x0;
	float dy = y1 - y0;
	int steps = (int)(abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
	float xinc = dx / steps;
	float yinc = dy / steps;
	
	for (int i = 0;i < steps;i++) {
		x += xinc;
		y += yinc;
		//printf("draw pixel (%d,%d) \n", ROUND(x), ROUND(y));
		draw_pixel_virtual(ROUND(x), ROUND(y),color);
	}
}

void Bersenham(int x0, int y0, int x1, int y1) {
	if (y1 > y0) {
		Bersenham_template(TO_VIRTUAL_PIXEL(x0), TO_VIRTUAL_PIXEL(y0), TO_VIRTUAL_PIXEL(x1), TO_VIRTUAL_PIXEL(y1));
	}
	else {
		Bersenham_template(TO_VIRTUAL_PIXEL(x1), TO_VIRTUAL_PIXEL(y1), TO_VIRTUAL_PIXEL(x0), TO_VIRTUAL_PIXEL(y0));
	}
}

static void Bersenham_template(int x0, int y0, int x1, int y1) {
	printf("Bersenham args (%d , %d , %d , %d)\n", x0, y0, x1, y1);
	draw_pixel_virtual(x0, y0,DEFAULT_COLOR);
	int x = x0;
	int y = y0;
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int p0;
	if(dy > dx){
		Bersenham_template_1(dy, dx, x0, y0, (x1 > x0));
	}
	else {
		Bersenham_template_1(dx, dy, x0, y0, (x1 > x0));
	}
}

// for 0<k <1
// degree 分为正向和反向
static void  Bersenham_template_1(int dx, int dy, int x, int y, int degree) {
	int p0;
	p0 = 2 * dy - dx;
	if (degree) {
		for (int i = 0; i < dx; i++) {
			if (p0 < 0) {
				draw_pixel_virtual(x + 1 + i, y,DEFAULT_COLOR);
				p0 = p0 + 2 * dy;
			}
			else {
				y++;
				draw_pixel_virtual(x + 1 + i, y,DEFAULT_COLOR);
				p0 = p0 + 2 * dy - 2 * dx;
			}
		}
	}
	else {
		for (int i = 0; i < dx; i++) {
			if (p0 < 0) {
				draw_pixel_virtual(x - 1 - i, y,DEFAULT_COLOR);
				p0 = p0 + 2 * dy;
			}
			else {
				y++;
				draw_pixel_virtual(x - 1 - i, y,DEFAULT_COLOR);
				p0 = p0 + 2 * dy - 2 * dx;
			}
		}
	}
}

void Init(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, 0.0, 1.0);
}

/*
int main() {
	int width, height;
	width = 1440;
	height = 960;

	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}
	window = glfwCreateWindow(width, height, "Computer Graphics", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	Init(width, height);
	int printed = 1;

	while (!glfwWindowShouldClose(window)) {

		//glClear(GL_COLOR_BUFFER_BIT);
		if (printed) {
			//Draw here
#ifdef DDA
			myDDA(100, 100, 600, 300);
			myDDA((float)100, (float)100, (float)200, (float)0);
			myDDA((float)100, (float)100, (float)105, (float)200);
			myDDA((float)100, (float)100, (float)70, (float)200);
			myDDA((float)100, (float)100, (float)0, (float)100);
			myDDA((float)100, (float)100, (float)200, (float)100);
#endif 

#ifdef BERSENHAM
			//Bersenham(0, 0, 500, 100);
			Bersenham(0, 0, 100, 500);
			Bersenham(0, 0, 0, 1000);
			Bersenham(1000, 500, 0, 0);
			Bersenham(1000, 200, 200, 800);
#endif 
		}
		draw_grid(width, height);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}*/