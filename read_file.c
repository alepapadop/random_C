#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 1024

FILE *open_file(char *filename);
void read_header(FILE *fp,int *header);
void read_nodes(FILE *fp,int num_of_nodes,float *x,float *y,float *z);
void read_elements(FILE *fp,int num_of_elements,int *efirst,int *esecond,int *ethird,int *efourth);
void read_vol(FILE *fp,int num_of_vols, int *vfirst,int *vsecond,int *vthird,int *vfourth,int *vfifth,int *vsixth,int *vseventh,int *veighth);


int main(){
	
	char filename[] = "test_data";
	FILE *fp;
	int i = 0;
	int *header;
	int size;
	float *x,*y,*z;
	int *efirst,*esecond,*ethird,*efourth;	
	int *vfirst,*vsecond,*vthird,*vfourth,*vfifth,*vsixth,*vseventh,*veighth;

	header = (int *)malloc(sizeof(int));
	
	fp = open_file(filename);		
		
	read_header(fp,header);

	x = (float *)malloc(sizeof(float)*header[0]);
	y = (float *)malloc(sizeof(float)*header[0]);
	z = (float *)malloc(sizeof(float)*header[0]);

	read_nodes(fp,header[0],x,y,z);

	efirst = (int *)malloc(sizeof(int)*header[1]);
	esecond = (int *)malloc(sizeof(int)*header[1]);
	ethird = (int *)malloc(sizeof(int)*header[1]);
	efourth = (int *)malloc(sizeof(int)*header[1]);

	read_elements(fp,header[1],efirst,esecond,ethird,efourth);

	vfirst = (int *)malloc(sizeof(int)*header[2]);
	vsecond = (int *)malloc(sizeof(int)*header[2]);
	vthird = (int *)malloc(sizeof(int)*header[2]);
	vfourth = (int *)malloc(sizeof(int)*header[2]);
	vfifth = (int *)malloc(sizeof(int)*header[2]);
	vsixth = (int *)malloc(sizeof(int)*header[2]);
	vseventh = (int *)malloc(sizeof(int)*header[2]);
	veighth = (int *)malloc(sizeof(int)*header[2]);

	read_vol(fp,header[2],vfirst,vsecond,vthird,vfourth,vfifth,vsixth,vseventh,veighth);

	fclose(fp);

}

void read_vol(FILE *fp,int num_of_vols, int *vfirst,int *vsecond,int *vthird,int *vfourth,int *vfifth,int *vsixth,int *vseventh,int *veighth)
{

	int i;
	char buffer[BUFFER];

	for(i=0;i<num_of_vols;i++){
	
		fgets(buffer,sizeof(buffer),fp);

		sscanf(buffer,"%d %d %d %d %d %d %d %d",vfirst+i,vsecond+i,vthird+i,vfourth+i,vfifth+i,vsixth+i,vseventh+i,veighth+i);

		printf("%d - %d - %d - %d - %d - %d - %d - %d\n",vfirst[i],vsecond[i],vthird[i],vfourth[i],vfifth[i],vsixth[i],vseventh[i],veighth[i]);	


	}

}


void read_elements(FILE *fp,int num_of_elements,int *efirst,int *esecond,int *ethird,int *efourth)
{

	int i;
	char buffer[BUFFER];

	for(i=0;i<num_of_elements;i++){
	
		fgets(buffer,sizeof(buffer),fp);

		sscanf(buffer,"%d %d %d %d",efirst+i,esecond+i,ethird+i,efourth+i);

		printf("%d - %d - %d -%d \n",efirst[i],esecond[i],ethird[i],efourth[i]);	


	}

}

void read_nodes(FILE *fp,int num_of_nodes,float *x,float *y,float *z)
{

	int i;
	char buffer[BUFFER];

	for(i=0;i<num_of_nodes;i++){

		fgets(buffer,sizeof(buffer),fp);

		sscanf(buffer,"%f %f %f",x+i,y+i,z+i);	

		printf("%f - %f - %f \n",x[i],y[i],z[i]);

	}

}

FILE *open_file(char *filename)
{
	FILE *fp;

	fp = fopen(filename,"r");

	if(fp != NULL)
		printf("Open File: %s \n",filename);
	else
		printf("Error Opening file:%s");

	return fp;

}

void read_header(FILE *fp,int *header)
{

	char buffer[BUFFER];
	char *parts;
	int i = 0;
	int size;
	int j;


	if(fgets(buffer,sizeof(buffer),fp)){

		parts = strtok(buffer, " " );

		while(parts != NULL){
				
			if(i > 0){

				size = sizeof(header)/sizeof(int);

				header = (int *)realloc(header,sizeof(int)*i);
				
				header[i] = atoi(parts);
				
			}else{

				header[0] = atoi(parts);

			}

			parts = strtok(NULL, " ");

			i++;

		}	

	}

}
