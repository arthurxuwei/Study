#include <stdlib.h>

#include "Circle.h"
#include "Square.h"



int
main(int argc, char* argv[]) {
	Shape myShape;
	Vector2 point, center;

	Vector2_init(&center, 0.0, 0.0);
	Vector2_init(&point, 0.9, 0.9);

	//Square_init(&myShape, &center, 1.0);
	Circle_init(&myShape, &center, 1.0);

	// DO THINGS WITH MY OBJECTS
	Shape_print(&myShape, stdout);
	if (Shape_isInside(&myShape, &point)) {
		printf("I AM IN THE SHAPE, YEAH !\n");
	}
	else {
		printf("I AM NOT IN THE SHAPE :(\n");
	}

	Shape_destroy(&myShape);
	return EXIT_SUCCESS;
}
