#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 1024
#define DEBUG 1

FILE *open_file(char *filename);
int * read_header(FILE *fp);
void read_nodes(FILE *fp,int num_of_nodes,float *x,float *y,float *z);
void read_elements(FILE *fp,int num_of_elements,int *e1,int *e2,int *e3,int *e4);
void read_vol(FILE *fp, int num_of_vols, int *v1, int *v2, int *v3, int *v4, int *v5, int *v6, int *v7, int *v8);
float *alloc_mem_nodes(int num_of_nodes);
int *alloc_mem_elements(int num_of_elements);
int *alloc_mem_volumes(int num_of_volumess);

int main(){
	
	char filename[] = "test_data";
	FILE *fp = NULL;
	int *header = NULL;
	float *x = NULL, *y = NULL, *z = NULL;
	int *e1 = NULL, *e2 = NULL, *e3 = NULL, *e4 = NULL;	
	int *v1 = NULL, *v2 = NULL, *v3 = NULL, *v4 = NULL, *v5 = NULL, *v6 = NULL, *v7 = NULL, *v8 = NULL;
	
	
	fp = open_file(filename);		
		
	header = read_header(fp);
	
	if(header [0]){

		x = alloc_mem_nodes(header[0]);	
		y = alloc_mem_nodes(header[0]);
		z = alloc_mem_nodes(header[0]);

		read_nodes(fp, header[0], x, y, z);
	}

	if(header[1]){
		
		e1 = alloc_mem_elements(header[1]);
		e2 = alloc_mem_elements(header[1]);
		e3 = alloc_mem_elements(header[1]);
		e4 = alloc_mem_elements(header[1]);

		read_elements(fp, header[1], e1, e2, e3, e4);
	}

	if(header[2]){

		v1 = alloc_mem_volumes(header[2]); 
		v2 = alloc_mem_volumes(header[2]); 
		v3 = alloc_mem_volumes(header[2]); 
		v4 = alloc_mem_volumes(header[2]); 
		v5 = alloc_mem_volumes(header[2]); 
		v6 = alloc_mem_volumes(header[2]); 
		v7 = alloc_mem_volumes(header[2]); 
		v8 = alloc_mem_volumes(header[2]); 

		read_vol(fp,header[2], v1, v2, v3, v4, v5, v6, v7, v8);

	}

	fclose(fp);

	return 0;

}

void read_vol(FILE *fp, int num_of_volumes, int *v1, int *v2, int *v3 ,int *v4, int *v5, int *v6, int *v7, int *v8)
{

	int i;
	char buffer[BUFFER];

	for(i=0; i < num_of_volumes; i++){
	
		fgets(buffer, sizeof(buffer), fp);

		sscanf(buffer, "%d %d %d %d %d %d %d %d", (v1 + i), (v2 + i), (v3 + i), (v4 + i), (v5 + i), (v6 + i), (v7 + i), (v8 + i));

		if(DEBUG) printf("%d - %d - %d - %d - %d - %d - %d - %d\n", v1[i], v2[i], v3[i], v4[i], v5[i], v6[i], v7[i], v8[i]);	


	}

}


void read_elements(FILE *fp, int num_of_elements, int *e1, int *e2, int *e3, int *e4)
{

	int i;
	char buffer[BUFFER];

	for(i=0; i < num_of_elements; i++){
	
		fgets(buffer, sizeof(buffer), fp);

		sscanf(buffer, "%d %d %d %d", (e1 + i), (e2 + i), (e3 + i), (e4 + i));

		if(DEBUG) printf("%d - %d - %d -%d \n", e1[i], e2[i], e3[i], e4[i]);	


	}

}

void read_nodes(FILE *fp, int num_of_nodes, float *x, float *y, float *z)
{

	int i;
	char buffer[BUFFER];

	for(i=0; i < num_of_nodes; i++){

		fgets(buffer, sizeof(buffer), fp);

		sscanf(buffer, "%f %f %f", (x + i), (y + i), (z + i));	

		if(DEBUG) printf("%f - %f - %f \n", x[i], y[i], z[i]);

	}

}

float *alloc_mem_nodes(int num_of_nodes){

	float *p;

	p = (float *)malloc(sizeof(float) * num_of_nodes);
	
	if( p == NULL){

		printf("ERROR: Problem allocating memory for nodes \n");
		exit(0);

	}

	return p;

}

int *alloc_mem_elements(int num_of_elements)
{

	int *p;

	p = (int *)malloc(sizeof(int) * num_of_elements);

	if( p == NULL ){

		printf("ERROR: Problem allocating memory for elements \n");
		exit(0);

	}
	
	return p;

	

}

int *alloc_mem_volumes(int num_of_volumes)
{
	
	int *p;

	p = (int *)malloc(sizeof(int) * num_of_volumes);
	
	if( p == NULL){

		printf("ERROR: Problem allocating memory for volumes \n");
		exit(0);

	}

	return p;


}

FILE *open_file(char *filename)
{
	FILE *fp;

	fp = fopen(filename,"r");

	if(fp != NULL)
		printf("Open File: %s \n",filename);
	else
		printf("Error Opening file:%s \n",filename);

	return fp;

}

int *read_header(FILE *fp)
{

	char buffer[BUFFER];
	char *parts;
	int i = 0;
	int *header;

	header = (int *)malloc(sizeof(int));

	if(fgets(buffer,sizeof(buffer), fp)){

		parts = strtok(buffer, " " );

		while(parts != NULL){
				
			if(i > 0){


				header = (int *)realloc(header,sizeof(int) * i);
				
				header[i] = atoi(parts);
				
			}else{

				header[0] = atoi(parts);

			}

			parts = strtok(NULL, " ");

			i++;

		}	

	}

	return header;

}
