#include <stdio.h>
#include <stdlib.h>

/*

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
*/

struct list
{
	int data;
	struct list *next;
	
	void (*print)(struct list *);
};



struct list *nil ()
{
	return 0;
}



struct list *cons (int data, struct list *next)
{
	struct list *l = (struct list *)malloc(sizeof(*l));
	l->data = data;
	l->next = next;
	return l;
}



/*
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
*/

/*
void print(struct list *l)
{
	printf( "%d->" , l->data);
}
*/

void pt (struct list *l)
{
	while (l)
	{
		printf ("%d,", l->data);
		l =l->next;
	}
}

int main( int argc, char* argv[] )
{
	struct list *l = cons(1, cons(2, cons(3, nil())));

	l->print = pt;

	l->print(l);
	
	return 0;
}


