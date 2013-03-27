#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Grid {

	int id;
	double x1,x2,x3;
};

struct Grid *alloc_space_struct(struct Grid *grid);

int struct_cmp(const void *a, const void *b);
int main()
{
	struct Grid *grid = NULL;
	int i;

	grid = malloc(sizeof(struct Grid));

	grid[0].id = 5;
	grid[0].x1 = 5;
	grid[0].x2 = 5;
	grid[0].x3 = 5;

	grid = alloc_space_struct(grid);
	
	for(i = 0; i < 5; i++ ) {
		printf("id: %d, x1: %lf, x2: %lf, x3: %lf \n", grid[i].id, grid[i].x1, grid[i].x2, grid[i].x3);
	}

	puts("");

	printf("grid %d \n", sizeof(grid));

	printf("grid %d \n", sizeof(struct Grid));

	qsort(grid, 5, sizeof(struct Grid), struct_cmp);
	
	puts("");

	for(i = 0; i < 5; i++ ) {
		printf("id: %d, x1: %lf, x2: %lf, x3: %lf \n", grid[i].id, grid[i].x1, grid[i].x2, grid[i].x3);
	}

	free(grid);
	return 0;	

}

struct Grid *alloc_space_struct(struct Grid *grid)
{
	int i = 0;

	grid = realloc(grid, 5 * sizeof(struct Grid));
	if (grid != NULL )
		printf("ok \n");
	for (i = 1; i < 5; i++) {
		grid[i].id = i;
		grid[i].x1 = i;
		grid[i].x2 = i;
		grid[i].x3 = i;
	}

	return grid;
}


int struct_cmp(const void *a, const void *b)
{
	struct Grid *ap = (struct Grid *)a;
	struct Grid *bp = (struct Grid *)b;

	//printf("Comp %d --  %d \n",ap->id,ap->id);

	if(ap->id > bp->id )
		return 1;
	else if (ap->id < bp->id)
		return -1;
	else
		return 0;
}
