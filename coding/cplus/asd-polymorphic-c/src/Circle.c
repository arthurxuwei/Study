#include <stdlib.h>
#include "Circle.h"


void
Circle_print(Shape* self, FILE* out) {
	Circle* circle;

	circle = (Circle*)self->data;

	fprintf(out, "circle(radius = %f)\n", circle->radius);
}



int
Circle_isInside(Shape* self, const Vector2* M) {
	Vector2 diff;
	Circle* circle;

	circle = (Circle*)self->data;
	
	Vector2_copy(&diff, &(circle->center));
	Vector2_sub(&diff, M);

	return Vector2_norm(&diff) < circle->radius;
}



void
Circle_destroy(Shape* self) {
	free(self->data);
}



ShapeDelegate CircleDelegate = {
	Circle_isInside,
	Circle_print,
	Circle_destroy
};



void
Circle_init(Shape* self, const Vector2* center, double radius) {
	Circle* data;

	
	data = (Circle*)malloc(sizeof(Circle));
	Vector2_copy(&(data->center), center);
	data->radius = radius;

	self->data = data;
	self->delegate = CircleDelegate;
}

