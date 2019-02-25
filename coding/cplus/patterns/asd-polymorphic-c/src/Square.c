#include <stdlib.h>
#include "Square.h"



void
Square_destroy(Shape* self) {
	free(self->data);
}



void
Square_print(Shape* self, FILE* out) {
	Square* square;

	square = (Square*)self->data;

	fprintf(out, "square(size = %f)\n", square->size);
}




int
Square_isInside(Shape* self, const Vector2* M) {
	Vector2 diff;
	Square* square;

	square = (Square*)self->data;
	
	Vector2_copy(&diff, &(square->center));
	Vector2_sub(&diff, M);
	Vector2_abs(&diff);

	return Vector2_max(&diff) < square->size;
}



ShapeDelegate SquareDelegate = {
	Square_isInside,
	Square_print,
	Square_destroy
};



void
Square_init(Shape* self, const Vector2* center, double size) {
	Square* data;

	
	data = (Square*)malloc(sizeof(Square));
	Vector2_copy(&(data->center), center);
	data->size = size;

	self->data = data;
	self->delegate = SquareDelegate;
}

