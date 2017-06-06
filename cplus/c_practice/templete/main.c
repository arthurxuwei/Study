#include <stdio.h>
#include <stdlib.h>


#define LIST(X)			  \
	struct list			  \
	{					  \
		X data;			  \
		struct list *next;\
	};					  \
struct list *cons (X data, struct list *next)           \
{														\
	struct list *l = (struct list *)malloc(sizeof(*l)); \
	l->data = data;										\
	l->next = next;										\
	return l;											\
}														\



LIST(int)





struct list *nil ()
{
	return 0;
}

/*

struct list *cons (int data, struct list *next)
{
	struct list *l = (struct list *)malloc(sizeof(*l));
	l->data = data;
	l->next = next;
	return l;
}

*/

void high_level_func ( void (*f)(struct list *l), struct list *l)
{
	switch ( (int)l )
	{
	case 0:
		printf(	"^" );
		return;
	default:
		f(l);
		high_level_func( f, l->next);
		return;
	}
}

void print(struct list *l)
{
	printf( "%d->" , l->data);
}

int main( int argc, char* argv[] )
{
	struct list *l = cons(1.5, cons(2.6, cons(3.7, nil())));
	high_level_func( print, l);
//	printf("%d",argc);
	return 0;
}