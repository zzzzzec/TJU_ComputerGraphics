#include "VertexList.h"

VertexList::VertexList(int size) {
	this->vertex_list = (Point*)malloc(sizeof(Point) * size);
	memset(this->vertex_list, 0, sizeof(Point) * size);

	this->vertex_list_temp = (Point*)malloc(sizeof(Point) * size);
	memset(this->vertex_list_temp, 0, sizeof(Point) * size);
	len = 0;
	temp_len = 0;
}

VertexList::~VertexList() {
	free(this->vertex_list);
}

void VertexList::append(Point p) {
	vertex_list[len].x = p.x;
	vertex_list[len].y = p.y;
	len += 1;
}

void VertexList::append(int x, int y) {
	vertex_list[len].x = x;
	vertex_list[len].y = y;
	len += 1;
}

void VertexList::append_temp(Point p)
{
	vertex_list_temp[temp_len].x = p.x;
	vertex_list_temp[temp_len].y = p.y;
	temp_len += 1;
}

void VertexList::append_temp(int x, int y)
{
	vertex_list_temp[temp_len].x = x;
	vertex_list_temp[temp_len].y = y;
	temp_len += 1;
}

void VertexList::draw_polygon(int color)
{
	if (len < 3) {
		printf("len < 3 ! bad arg \n");
		exit(-1);
	}
	for (int i = 0; i < len - 1;i++) {
		myDDA(vertex_list[i], vertex_list[i + 1],color);
	}
	myDDA(vertex_list[len - 1], vertex_list[0],color);
}

void VertexList::copy()
{
	memcpy(vertex_list, vertex_list_temp, temp_len * (sizeof(Point)));
	len = temp_len;
	memset(vertex_list_temp, 0, temp_len * (sizeof(Point)));
	temp_len = 0;
}
