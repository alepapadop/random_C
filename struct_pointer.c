#include <stdio.h>
#include <stdlib.h>

typedef struct Elem {
	int id;
} Elem;

typedef struct Grid {
	Elem *ptr;
	int x;
} Grid;

int main()
{
	
	Elem **tmp = NULL;
	Elem *elem = malloc(sizeof(Elem));
	Grid *grid = malloc(sizeof(Grid));


	grid->ptr = elem;
	grid->ptr->id = 7;

	tmp = (Elem **)grid;
	
	printf("elem->id %d\n", (*tmp)->id);
	printf("grid->ptr->id %d\n", grid->ptr->id);

	free(elem);
	free(grid);
	
	return 1;
}
