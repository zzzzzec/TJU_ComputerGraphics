#pragma once
#define HAVE_STRUCT_TIMESPEC

#include<iostream>
#include<math.h>
#include<GLFW/glfw3.h>
#include<gl/GL.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>

#define ROUND(x) ((int)(x + 0.5))
#define PIXEL 5
#define TO_VIRTUAL_PIXEL(real) (real/PIXEL) 
#define TO_REAL_PIXEL(x) (x*PIXEL)

#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define DEFAULT_COLOR red
enum {red , blue , yellow , white};

typedef struct {
	int x;
	int y;
}Point;

typedef struct {
	Point start;
	Point end;
}Line;

void Init(int width, int height);
void draw_pixel_virtual(int x, int y, int color);
void draw_pixel_real(int x, int y, int color);
void draw_grid(int width, int heigh);

void myDDA(Point start, Point end, int color);
void Bersenham(int x0, int y0, int x1, int y1);

#include "VertexList.h"