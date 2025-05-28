#include <stdbool.h>
#include "Circle.h"

/**
 * @see Shape.cpp
 */
Circle *Circle_Self(Shape *self)
{
    return (Circle *)self->pDerivedObj;
}
Shape *New_Circle(double x, double y, double r)
{
    Circle *pDerivedObj = (Circle *)malloc(sizeof(Circle));
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->r = r;
    Shape *pObj = New_Shape();
    pObj->overlap = Circle_overlap;
    pObj->center_x = Circle_center_x;
    pObj->center_y = Circle_center_y;
    pObj->update_center_x = Circle_update_center_x;
    pObj->update_center_y = Circle_update_center_y;
    pObj->get_top = Circle_get_top;
	pObj->get_bottom = Circle_get_bottom;
	pObj->get_left = Circle_get_left;
	pObj->get_right = Circle_get_right;
    pObj->getType = Circle_getType;
    pObj->pDerivedObj = pDerivedObj;
    return pObj;
}
double Circle_center_x(Shape *self)
{
    return Circle_Self(self)->x;
}
double Circle_center_y(Shape *self)
{
    return Circle_Self(self)->y;
}
void Circle_update_center_x(Shape *self, int x)
{
    Circle_Self(self)->x += x;
}
void Circle_update_center_y(Shape *self, int y)
{
    Circle_Self(self)->y += y;
}
double Circle_get_top(Shape *self) {
	return Circle_Self(self)->y - Circle_Self(self)->r;
}

double Circle_get_bottom(Shape *self) {
	return Circle_Self(self)->y + Circle_Self(self)->r;
}

double Circle_get_left(Shape *self) {
	return Circle_Self(self)->x - Circle_Self(self)->r;
}

double Circle_get_right(Shape *self) {
	return Circle_Self(self)->x + Circle_Self(self)->r;
}
ShapeType Circle_getType()
{
    return CIRCLE;
}
