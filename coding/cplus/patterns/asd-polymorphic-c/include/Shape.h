#ifndef KUAI_GUI_SHAPE_H
#define KUAI_GUI_SHAPE_H

#include <stdio.h>
#include "Vector2.h"

#ifdef __cplusplus
extern "C" {
#endif



struct s_Shape;

typedef struct {
	/* Check if a point is inside a shape */
	int(*isInside)(struct s_Shape* self, const Vector2*);

	/* Output to a file a description of a shape  */
	void(*print)(struct s_Shape* self, FILE* out);

	/* Called upon destruction */
	void(*destroy)(struct s_Shape* self);
} ShapeDelegate;



struct s_Shape {
	void* data;
	ShapeDelegate delegate;
};

typedef struct s_Shape Shape;



extern void
Shape_destroy(Shape* self);

extern int
Shape_isInside(Shape* self, const Vector2* M);

extern void
Shape_print(Shape* self, FILE* out);



#ifdef __cplusplus
}
#endif

#endif /* KUAI_GUI_SHAPE_H */
