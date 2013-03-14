#include <stdio.h>
#include <string.h>


#define HEADER_VALUES 2
#define BUFFER_SIZE 1024


int main(){

	
	char filename[] = "test_data";
	FILE *fp = NULL;
	char buffer[BUFFER_SIZE];
	char *parts;
	fpos_t pos;
	fpos_t pos_array[10];
	int i = 0;

	fp = fopen(filename,"r");
	
	if(fp != NULL){

		printf("File is Open. The filename is %s \n ",filename);
		

		while(fgets(buffer, BUFFER_SIZE,fp)){



			puts(buffer);
			parts = strtok(buffer," ");
			
			fgetpos(fp,&pos);
			
			pos_array[i] = pos;

			while(parts != NULL ){

				printf("%s \n",parts);
				
				parts = strtok(NULL," ");
			}


			i++;


		}
		
		

	}else{

		printf("Could not open the file");

	}


	printf("%d \n", pos_array[0]);

	printf("%d \n", pos_array[1]);


	printf("%d \n", pos_array[2]);

	fsetpos(fp, &pos_array[1]);

	
	fgets(buffer, BUFFER_SIZE,fp);
	puts(buffer);

	
		

	fclose(fp);

}


