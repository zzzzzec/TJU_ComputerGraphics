#include "common.h"
#define COHENSU 
#define LEFT_MASK (0b00000001)
#define RIGHT_MASK (0b00000010)
#define TOP_MASK (0b00001000)
#define BOTTOM_MASK (0b00000100)

enum { LEFT , RIGHT , TOP , BOTTOM };

typedef struct {
	Point start;
	Point end;
	int left;
	int right;
	int top;
	int bottom;
}Bound;

VertexList vlist(100);
Bound bound;
//pthread_mutex_t mutex;
//pthread_cond_t cond;

static void SutherHodg_template(VertexList* vlist, int LRTB);
static void get_intersection(Point* intersection, Point a, Point b, int LRTB);
static void check_point(Point a, Point b, int LRTB);
//static void* console(void* arg);

void set_bound(Bound* bound, int x0 , int y0 ,int x1 , int y1) {

	(*bound).start.x = 200;
	(*bound).start.y = 200;
	(*bound).end.x = 600;
	(*bound).end.y = 600;
	(*bound).left =   MIN(x0, x1);
	(*bound).right =  MAX(x0, x1);
	(*bound).top =    MAX(y0, y1);
	(*bound).bottom = MIN(y0, y1);
}

void draw_bound(Bound bound, int color) {
	//无所谓顺序，只需要令ab为对角即可
	Point a, b, c, d;
	a = bound.start;
	b = bound.end;

	c.x = bound.start.x;
	c.y = bound.end.y;

	d.x = bound.end.x;
	d.y = bound.start.y;

	myDDA(a, c,color);
	myDDA(a, d,color);
	myDDA(b, c,color);
	myDDA(b, d,color);

}

static unsigned short cohenSutherlandEncode(Point a) {
	unsigned short code = 0;
	if (a.x < bound.left) {
		code = code | LEFT_MASK;
	}
	if(a.x > bound.right)
	{
		code = code | RIGHT_MASK;
	}
	if (a.y < bound.bottom) {
		code = code | BOTTOM_MASK;
	}
	if(a.y > bound.top)
	{
		code = code | TOP_MASK;
	}
	return code;
}



void cohenSutherland(Point a,Point b) {
	unsigned short codeA = cohenSutherlandEncode(a);
	unsigned short codeB = cohenSutherlandEncode(b);
	Point tempa = a;
	Point tempb = b;
	if (codeA & codeB) {
		return;
	}
	Point intersection;
	intersection.x = 0;
	intersection.y = 0;
	if (!(tempa.x > bound.left && tempb.x > bound.left)) {
		get_intersection(&intersection, tempa, tempb, LEFT);
		tempb = (tempa.x > tempb.x) ? tempa : tempb;
		tempa = intersection;
	}
	if (!(tempa.x < bound.right && tempb.x < bound.right)) {
		get_intersection(&intersection, tempa, tempb, RIGHT);
		tempb = (tempa.x < tempb.x) ? tempa : tempb;
		tempa = intersection;
	}
	if (!(tempa.y < bound.top && tempb.y < bound.top)) {
		get_intersection(&intersection, tempa, tempb, TOP);
		tempb = (tempa.y < tempb.y) ? tempa : tempb;
		tempa = intersection;
	}
	if (!(tempa.y > bound.bottom && tempb.y > bound.bottom)) {
		get_intersection(&intersection, tempa, tempb, BOTTOM);
		tempb = (tempa.y > tempb.y) ? tempa : tempb;
		tempa = intersection;
	}
	myDDA(tempa, tempb, white);
}

void SutherHodg(VertexList* vlist) {
	SutherHodg_template(vlist, LEFT);
	SutherHodg_template(vlist, RIGHT);
	SutherHodg_template(vlist, TOP);
	SutherHodg_template(vlist, BOTTOM);
}

static void SutherHodg_template(VertexList* vlist , int LRTB) {
	for (int i = 0; i < (*vlist).len - 1 ; i++)
	{
		check_point((*vlist).vertex_list[i], (*vlist).vertex_list[i + 1], LRTB);
	}
	check_point((*vlist).vertex_list[(*vlist).len-1], (*vlist).vertex_list[0], LRTB);
	(*vlist).copy();
}

static void check_point(Point a, Point b, int LRTB) {
	Point intersection;
	switch (LRTB)
	{
	case LEFT:  
		if (a.x < bound.left){
			if (b.x < bound.left) {
				goto out_out;
			}
			else {
				goto out_in;
			}
		}
		else {
			if (b.x > bound.left) {
				goto in_in;
			}
			else {
				goto in_out;
			}
		}
		break;
	case RIGHT:
		if (a.x > bound.right) {
			if (b.x > bound.right) {
				goto out_out;
			}
			else {
				goto out_in;
			}
		}
		else {
			if (b.x < bound.right) {
				goto in_in;
			}
			else {
				goto in_out;
			}
		}
		break;
	case TOP:
		if (a.y > bound.top) {
			if (b.y > bound.top) {
				goto out_out;
			}
			else {
				goto out_in;
			}
		}
		else {
			if (b.y < bound.top) {
				goto in_in;
			}
			else {
				goto in_out;
			}
		}
		break;
	case BOTTOM:
		if (a.y < bound.bottom) {
			if (b.y < bound.bottom) {
				goto out_out;
			}
			else {
				goto out_in;
			}
		}
		else {
			if (b.y > bound.bottom) {
				goto in_in;
			}
			else {
				goto in_out;
			}
		}
		break;
	default:
		printf("check_point : uncognized case ");
		exit(-1);
		break;
	}

out_out:
	return;
out_in:
	get_intersection(&intersection,a,b,LRTB);
	vlist.append_temp(intersection);
	vlist.append_temp(b);
 	return;
in_in:
	vlist.append_temp(b);
	return;
in_out:
	get_intersection(&intersection, a, b, LRTB);
	vlist.append_temp(intersection);
	return;
}


static void draw_intersection(Point* vertex_list , int len) {
	Point intersection;
	for (int i = 0; i < len - 1;i++) {
		get_intersection(&intersection, vertex_list[i], vertex_list[i + 1], LEFT);
		draw_pixel_real(intersection.x, intersection.y, blue);
	}
}

static void get_intersection(Point* intersection, Point a, Point b, int LRTB) {
	float k = abs( ( ( (float)(a.y - b.y)) / ((float)(a.x - b.x)) ));
	int temp;
	switch (LRTB)
	{
		case LEFT:
			(*intersection).x = bound.left;
			if (a.y > b.y)
				temp =abs( b.x - bound.left);
			else
				temp =abs( a.x - bound.left);
			(*intersection).y = ROUND(( MIN(a.y, b.y) + k * temp ));
			break;
		case RIGHT:
			(*intersection).x = bound.right;
			if (a.y > b.y)
				temp = abs(b.x - bound.right);
			else
				temp = abs(a.x - bound.right);
			(*intersection).y = ROUND((MIN(a.y, b.y) + k * temp));
			break;
		case TOP:
			(*intersection).y = bound.top;
			if (a.x > b.x)
				temp = abs(b.y - bound.top);
			else
				temp = abs(a.y - bound.top);
			(*intersection).x = ROUND((MIN(a.x, b.x) + temp/k));
			break;
		case BOTTOM:
			(*intersection).y = bound.bottom;
			if (a.x > b.x)
				temp = abs(b.y - bound.bottom);
			else
				temp = abs(a.y - bound.bottom);
			(*intersection).x = ROUND((MIN(a.x, b.x) + temp / k));
			break;
	default:
		break;
	}
	//printf("intersection (%d,%d) + (%d,%d) = (%d,%d)\n", a.x, a.y, b.x, b.y, (*intersection).x, (*intersection).y);
}


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

	set_bound(&bound, 200, 200, 600, 600);

	Point p1, p2, p3, p4;
	p1.x = 400; p1.y = 800;
	p2.x = 100; p2.y = 400;
	p3.x = 500; p3.y = 150;
	p4.x = 700; p4.y = 450;

	vlist.append(p1);
	vlist.append(p2);
	vlist.append(p3);
	vlist.append(p4);

	Point a, b;
	a.x = 100;a.y = 150;
	b.x = 800;b.y = 700;

	while (!glfwWindowShouldClose(window)) {
		draw_grid(width,height);
		draw_bound(bound,red);
		vlist.draw_polygon(red);
		//SutherHodg(&vlist);
		//vlist.draw_polygon(yellow);
		myDDA(a, b, red);
		cohenSutherland(a, b);
		for (int i = 0; i < vlist.len - 1; i++)
		{
			cohenSutherland(vlist.vertex_list[i], vlist.vertex_list[i + 1]);
		}
		cohenSutherland(vlist.vertex_list[vlist.len - 1], vlist.vertex_list[0]);

		glfwSwapBuffers(window);	
		glfwPollEvents();
		while (1);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}