#include <math.h>
#include "Vector2.h"



void
Vector2_init(Vector2* self, double x, double y) {
	self->coeffs[0] = x;
	self->coeffs[1] = y;
}


void
Vector2_copy(Vector2* self, const Vector2* other) {
	int i;

	for(i = 0; i < 2; ++i)
		self->coeffs[i] = other->coeffs[i];
}




void
Vector2_add(Vector2* self, const Vector2* other) {
	int i;

	for(i = 0; i < 2; ++i)
		self->coeffs[i] += other->coeffs[i];
}




void
Vector2_sub(Vector2* self, const Vector2* other) {
	int i;

	for(i = 0; i < 2; ++i)
		self->coeffs[i] -= other->coeffs[i];
}




double
Vector2_dot(const Vector2* self, const Vector2* other) {
	int i;
	double sum;

	sum = 0.;
	for(i = 0; i < 2; ++i)
		sum += self->coeffs[i] * other->coeffs[i];

	return sum;
}



double
Vector2_norm(const Vector2* self) {
	return sqrt(Vector2_dot(self, self));
}



double
Vector2_min(const Vector2* self) {
	return fmin(self->coeffs[0], self->coeffs[1]);
}




double
Vector2_max(const Vector2* self) {
	return fmax(self->coeffs[0], self->coeffs[1]);
}



void
Vector2_abs(Vector2* self) {
	int i;

	for(i = 0; i < 2; ++i)
		self->coeffs[i] = fabs(self->coeffs[i]);
}
