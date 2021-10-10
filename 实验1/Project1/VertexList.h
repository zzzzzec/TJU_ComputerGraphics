#pragma once
#include "common.h"
class VertexList
{
public:
	Point* vertex_list;
	Point* vertex_list_temp;
	VertexList(int size);
	~VertexList();

	void append(Point p);
	void append(int x, int y);
	void append_temp(Point p);
	void append_temp(int x, int y);
	void draw_polygon(int color);
	void copy();

	int len;
	int temp_len;
};

