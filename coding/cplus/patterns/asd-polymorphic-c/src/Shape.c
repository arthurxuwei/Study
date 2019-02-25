#include "Shape.h"



void
Shape_destroy(Shape* self) {
	self->delegate.destroy(self);	
}



void
Shape_print(Shape* self, FILE* out) {
	self->delegate.print(self, out);	
}



int
Shape_isInside(Shape* self, const Vector2* M) {
	return self->delegate.isInside(self, M);
}
