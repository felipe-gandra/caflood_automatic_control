#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if (argc != 5){
        printf("The program needs 4 arguments. The execution line must be:\n./autocaflood <input folder dir> <input file> <parameter's file directory> <output folder dir>\n\n");
        exit(1);
    }
    
    Parameter *roughness = initParameter("Roughness Global");
    Parameter *elevation = initParameter("Elevation ASCII");
    char parameterFile[50]; strcpy(parameterFile, argv[3]);

    readData(parameterFile, roughness);
    readData(parameterFile, elevation);

    int nOutputs = roughness->count * elevation->count;
    char **outputList;
    char inputFile[50]; strcpy(inputFile, argv[2]);
    char inputDir[50]; strcpy(inputDir, argv[1]);
    char outputFolder[50]; strcpy(outputFolder, argv[4]);
    
    createOutputList(roughness, elevation, &outputList);
    createOutputFolders(nOutputs, outputFolder, outputList);

    time_t begin;
    time_t end;
    createTimeFile();

    //main loop
    for (int i = 0; i<roughness->count; i++){
        changeParameter(roughness->name, roughness->array[i], inputFile, inputDir);
        
        for (int j = 0; j<elevation->count; j++){                                      
            changeParameter(elevation->name, elevation->array[j], inputFile, inputDir);

                                                                            //currently output folder
            char *args[] = {"./caflood", "-WCA2D", inputDir, inputFile, strcat(outputList[elevation->count*i+j], "/"), NULL};
            
            time(&begin);
            runCaflood(args);

            time(&end);
            printTime(begin, end, outputList[elevation->count*i+j]);
        }
    }
    
    freeArray((void***)&outputList, nOutputs);
    freeArray((void***)&(roughness->array), 30);
    freeArray((void***)&(elevation->array), 30);


    return 0;
}