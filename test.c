#include <stdio.h>
#include <stdlib.h>

void point(int *p);

int main(){


	int *p;
	int x;


	p = &x;
	//*p =10;

	//printf("before ->  %d \n",*p);

	point(p);


	printf("out ->  %d \n",p[0]);



}

void point(int *p){


	p = (int *)malloc(sizeof(int)*1);
	p[0] = 10;

	printf("inside ->  %d \n",p[0]);

}
