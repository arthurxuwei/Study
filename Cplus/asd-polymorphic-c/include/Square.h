#ifndef KUAI_GUI_SQUARE_H
#define KUAI_GUI_SQUARE_H

#include "Shape.h"
#include "Vector2.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef struct {
	Vector2 center;
	double size;
} Square;



extern void
Square_init(Shape* self, const Vector2* center, double size);



#ifdef __cplusplus
}
#endif

#endif /* KUAI_GUI_SQUARE_H */
