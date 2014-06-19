#ifndef KUAI_GUI_VECTOR2_H
#define KUAI_GUI_VECTOR2_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct {
	double coeffs[2];
} Vector2;



extern void
Vector2_init(Vector2* self, double x, double y);

extern void
Vector2_copy(Vector2* self, const Vector2* other);

extern void
Vector2_add(Vector2* self, const Vector2* other);

extern void
Vector2_sub(Vector2* self, const Vector2* other);

extern double
Vector2_dot(const Vector2* self, const Vector2* other);

extern double
Vector2_min(const Vector2* self);

extern double
Vector2_max(const Vector2* self);

extern double
Vector2_norm(const Vector2* self);

extern void
Vector2_abs(Vector2* self);



#ifdef __cplusplus
}
#endif

#endif /* KUAI_GUI_VECTOR2_H */
