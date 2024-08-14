#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>


typedef struct DATA{
    char name[20];
    char ** array;
    int count;
}Data;


void freeArray(void **array, int n)
{
    if (array == NULL)
    {
        printf("The pointer was NULL\n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        if (array[i] != NULL)
        {
            free(array[i]);
            array[i] = NULL;
        }
    }
    free(array);
    array = NULL;
}


/*
Function to create a txt file (called time.txt) to store the execution time of each
parameter combination
*/
void createTimeFile(void)
{	
	FILE *file = fopen("time.txt", "w");
	if (file == NULL)
	{
		printf("Couldn't create file time.txt\n");
		exit(1);
	}
	fclose(file);
    file = NULL;
}


/*
Function to print the execution times in the time file
*/
void printTime(int begin, int end, char *name)
{
	FILE *file = fopen("time.txt", "r+");
	if (file == NULL)
	{
		printf("Couldn't open file time.txt\n");
		exit(1);
	}
	int time = end-begin;
	fseek(file, 0, SEEK_END);
	fprintf(file, "%s  %ds\n", name, time);
	fclose(file);
}


/*
Function to read and save all values of a certain parameter.It is used to save the list of 
parameters that are going to be used.
*/
void saveValues(Data * parameter)
{   
    char * value;
    while ((value = strtok(NULL, ",\n")) != NULL)
    {
        strcpy(parameter->array[parameter->count], value);
        parameter->count++;
    }
}

void readData()
{
    
}