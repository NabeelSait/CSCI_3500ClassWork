//Nabeel Sait and Cemil Can Ali Marandi
//1/24/2020
//This program illustrates some uses of pointers in C

#include <stdio.h>

char linString[] = "Linux!";
int  linSize = 6;

char *winString = "Windows!";
int  winSize = 8;

int numbers[] = { 4, 8, 15, 16, 23, 42 };

int main ( int argc, char* argv[] ){
	
	printf("%s\n", linString);
	printf("%s\n", winString);
	
 	int i;
	for (i=0; i < linSize; i++)
	{
	   printf("%c\n", linString[i]);
	}
	
	for (i = 0; i <winSize; i++)
	{
	   printf("%c\n", *(winString + i));
 	}

        for (i = 0; i <winSize; i++)
        {
           printf("%s\n", winString + i);
        }

	linString[0] = 'M';
	linString[3] = 'i';
	printf("%s\n", linString);

	printf("%d\n", sizeof( char ));
	printf("%d\n", sizeof( int ));

	int *first = numbers;
	int *third = &(numbers[2]);
	printf("%p\n", first);
	printf("%p\n", third);
	return 0;
}
