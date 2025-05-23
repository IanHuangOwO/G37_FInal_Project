#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>

typedef enum ShapeType
{
	POINT,
	RECTANGLE,
	CIRCLE
} ShapeType;

/**
 * @brief Base shape class.
 * @details The functions of its derived classes are all defined in Shape.c.
 * @see Shape.c
 */

typedef struct _Shape Shape;
typedef bool (*fptrOverlap)(Shape *, Shape *);
typedef double (*fptrCenterX)(Shape *);
typedef double (*fptrCenterY)(Shape *);
typedef void (*fptrUpdateCenterX)(Shape *, int);
typedef void (*fptrUpdateCenterY)(Shape *, int);
typedef double (*fptrget_top)(struct _Shape *self);
typedef double (*fptrget_bottom)(struct _Shape *self);
typedef double (*fptrget_left)(struct _Shape *self);
typedef double (*fptrget_right)(struct _Shape *self);
typedef ShapeType (*fptrGetType)();
struct _Shape
{
	void *pDerivedObj;
	fptrOverlap overlap;
	fptrCenterX center_x;
	fptrCenterY center_y;
	fptrUpdateCenterX update_center_x;
	fptrUpdateCenterY update_center_y;
	fptrget_top get_top;
	fptrget_bottom get_bottom;
	fptrget_left get_left;
	fptrget_right get_right;
	fptrGetType getType;
};
Shape *New_Shape();

#endif
