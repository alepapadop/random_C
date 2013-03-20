#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_numeric(char *string);

int main(){

	int value;

	char *p = "12" ;

	value = is_numeric(p);

	printf("The returned value is %d \n", value);

	return 0;

}


// Returns 1 if the string is numeric and 0 if not
int is_numeric(char * string)
{

        int i;
        int flag = 1;

        i = 0;

	while( *(string + i) != '\0'){

	        if(isdigit(*(string + i)) == 0  )
        	{
        		flag = 0;
   			break;
        	}

        	i++;
        }

        return flag;

}
