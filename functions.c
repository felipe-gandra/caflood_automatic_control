#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>


typedef struct PARAMETER Parameter;


Parameter * initParameter(char * parameterName)
{   
    Parameter * parameter;
    parameter = (Parameter *) malloc(sizeof(Parameter));
    if (parameter == NULL)
    {
        printf("Couldn't alocate memory to parameter struct\n");
        exit(1);
    }
    parameter->array = (char **) malloc(30*sizeof(char *));
    if (parameter->array == NULL)
    {
        printf("Couldn't alocate memory to array in struct\n");
        exit(1);
    }
    for (int i = 0; i<30; i++)
    {
        parameter->array[i] = (char *) malloc(30*sizeof(char));
        if (parameter->array[i] == NULL)
        {
            printf("Couldn't alocate memory to array[i] in struct\n");
            exit(1);
        }
    }
    strcpy(parameter->name, parameterName);
    parameter->count = 0;

    return parameter;
}

void freeArray(void ***array, int n)
{
    if (array == NULL || *array == NULL)
    {
        printf("The pointer was NULL\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        free((*array)[i]);
    }
    free(*array);
    *array = NULL;
}


/*
Function to create a txt file (called time.txt) to store the execution time of each
parameter combination
*/
void createTimeFile(void)
{	   
    FILE * file;
    FILE * exists = fopen("time.txt", "r");
    if (exists == NULL){
        fclose(exists); //the file doesn't exist
        file = fopen("time.txt", "w");
    }
    else{
        fclose(exists);  //the file already exists
        exists = NULL;
        file = fopen("time.txt", "r+");
    }

	if (file == NULL)
	{
		printf("Couldn't open/create file time.txt\n");
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
        if (parameter->count >=30){
            printf("Max number of parameter values (30) execedeed\n");
            exit(1);
        }
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

/*Currently this funcion can only work with Roughness Global and Elevation ASCII paremeters.
The user can change this function and the 'createOutputFolders' if he wants to change another parameter.*/
void createOutputList(Parameter * Roughness, Parameter *Elevation, char *** outputList)
{
    int nOutputs = Roughness->count * Elevation->count;

    //allocating memory
    *outputList = (char **) malloc(nOutputs*sizeof(char *));
    if (*outputList == NULL)
    {
        printf("Couldn't allocate memory to outputList array\n");
        exit(1);
    }
    for (int i = 0; i<nOutputs; i++)
    {
        (*outputList)[i] = malloc(40*sizeof(char));
        if ((*outputList)[i] == NULL)
        {
            printf("Couldn't allocate memory to outputList[i] array\n");
            exit(1);
        }
    }
    for (int i = 0; i<Roughness->count; i++)
    {
        for (int j = 0; j<Elevation->count; j++)
        {
            char sliceRoughness[10];
            char sliceElevation[10];

            sscanf(Roughness->array[i], "%*[^0-9]%5[^ ]", sliceRoughness);   // formatting strings
            sscanf(Elevation->array[j], "%*[^0-9]%5[^.]", sliceElevation);

            snprintf((*outputList)[i * (Elevation->count) + j], 40, "%s_%s", sliceRoughness, sliceElevation);
        }
    }
}

void createOutputFolders(int nOutputs, char * outputFolder, char ** outputList)
{   
    for (int i = 0; i<nOutputs;i++){	
		char name[20] = {"./"};
		strcat(name, outputFolder);
		strcat(name, outputList[i]);
		strcpy(outputList[i], name);

		if(mkdir(name, 0700))
		{	
			printf("Can't create new output folders. Check if there is any old folder in the directory.\n");
			exit(1);
		}
	}
}

char ** createSimNames(char ** outputList, int nOutputs){
    char ** simNames = (char **)malloc(sizeof(char*)*nOutputs);
    if (simNames == NULL){
        printf("Couldn't allocate memory\n");
        exit(1);
    }
    for (int i = 0; i<nOutputs; i++){
        simNames[i] = (char *) malloc(sizeof(char)*20);
        if (simNames[i] == NULL){
            printf("Couldn't allocate memory\n");
            exit(1);
        }

        strcpy(simNames[i], outputList[i]);
        memmove(simNames[i]+1, simNames[i], strlen(simNames[i]));
        simNames[i][0] = ' ';
    }
    return simNames;
}


void changeParameter(char * parameterName, char * newValue, char * inputFile, char * inputDir)
{   
    char copyInputDir[40]; strcpy(copyInputDir, inputDir);
    char tempDir[40];
    strcpy(tempDir, inputDir);
    strcat(tempDir, "temp.csv\0");  //temporary file directory
    strcat(copyInputDir, inputFile);

    FILE *file = fopen(copyInputDir, "r");  //input file
    if (file == NULL){
        printf("Couldn't open input file\n");
        exit(1);
    }

    FILE *tempFile = fopen(tempDir, "w+");
    if (tempFile == NULL){
        printf("Couldn't create temporary file\n");
        exit(1);
    } 
    char line[100];
    char tempLine[100];
    char * parameter;

    while (fgets(line, 100, file) != NULL){
        strcpy(tempLine, line);
        parameter = strtok(tempLine, "\t\t,");
        if (strcmp(parameter, parameterName) == 0){  //found the line that needs to be changed
            fprintf(tempFile, "%s\t\t,%s\n", parameterName, newValue);  //write the new parameter value in the temp file
        }
        else{  //wrong line: just copy to the new file
            fprintf(tempFile, "%s", line);
        }   
    }
    fclose(file); file = NULL;
    fclose(tempFile); tempFile = NULL;
    if (remove(copyInputDir) != 0){
        printf("Couldn't delete file while changing parameter value\n");
        exit(1);
    }
    if (rename(tempDir, copyInputDir))
    {
        printf("Couldn't rename temporary file\n");
        exit(1);
    }
}


void runCaflood(char ** args)
{
    pid_t pid = fork();

	if (pid == -1){
		printf("Couldn't create child process\n");
        exit(1);
	}
	else if (pid == 0){
	    execv("./caflood", args);
	    printf("Couldn't execute CAFlood\n");
		
	}
	else{     
	    int status;
		waitpid(pid, &status, 0);  //wait until the child's process is over
	}
}