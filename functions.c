#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>


typedef struct PARAMETER{
    char name[20];
    char ** array;
    int count;
}Parameter;

void initParameter(Parameter * parameter, char * parameterName)
{
    parameter = (Parameter *) malloc(sizeof(Parameter));
    if (parameter == NULL)
    {
        printf("Couldn't alocate memory to parameter struct\n");
        exit(1);
    }
    parameter->array = (char **) malloc(15*sizeof(char *));
    if (parameter->array == NULL)
    {
        printf("Couldn't alocate memory to array in struct\n");
        exit(1);
    }
    for (int i = 0; i<15; i++)
    {
        parameter->array[i] = (char *) malloc(30*sizeof(char));
        if (parameter->array[i] == NULL)
        {
            printf("Couldn't alocate memory to array[i] in struct\n");
            exit(1);
        }
    }
    strcpy(parameter->name, parameterName);
}

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
void saveValues(Parameter * parameter)
{   
    char * value;
    while ((value = strtok(NULL, ",\n")) != NULL)
    {
        strcpy(parameter->array[parameter->count], value);
        parameter->count++;
    }
}

void readData(char *fileName, Parameter * parameter)
{
    //opening file with parameter values
    FILE * file = fopen(fileName, "r+");
    if (file == NULL)
    {
        printf("Couldn't open file with parameter values\n");
        exit(1);
    }

    char line[250];
    char * parameterName;
    while (fgets(line, 250, file) != NULL)  //search for parameter name
    {
        parameterName = strtok(line, ",");
        if (strcmp(parameterName, parameter->name) == 0)  //found the correct line
        {
            saveValues(parameter);  //catch values and save
        }
    }

    fclose(file);
    file = NULL;
}