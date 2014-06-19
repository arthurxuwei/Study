#ifndef KUAI_GUI_CIRCLE_H
#define KUAI_GUI_CIRCLE_H

#include "Shape.h"
#include "Vector2.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef struct {
	Vector2 center;
	double radius;
} Circle;



extern void
Circle_init(Shape* self, const Vector2* center, double radius);



#ifdef __cplusplus
}
#endif

#endif /* KUAI_GUI_CIRCLE_H */
