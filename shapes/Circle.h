#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include <stdbool.h>
#include "Shape.h"

/**
 * @see Shape.cpp
 */
typedef struct _Circle
{
    double x, y, r;
} Circle;
Circle *Circle_Self(Shape *self);
bool Circle_overlap(Shape *self, Shape *tar);
double Circle_center_x(Shape *self);
double Circle_center_y(Shape *self);
void Circle_update_center_x(Shape *self, int x);
void Circle_update_center_y(Shape *self, int y);
double Circle_get_top(Shape *self);
double Circle_get_bottom(Shape *self);
double Circle_get_left(Shape *self);
double Circle_get_right(Shape *self);
ShapeType Circle_getType();
Shape *New_Circle(double x, double y, double r);
ShapeType Circle_getType();
#endif