#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(){   
    Parameter *roughness = initParameter("Roughness Global");
    Parameter *elevation = initParameter("Elevation ASCII");

    readData("dados.csv", roughness);
    readData("dados.csv", elevation);

    char **outputList;
    int nOutputs = roughness->count * elevation->count;

    createOutputList(roughness, elevation, &outputList);
    createOutputFolders(nOutputs, "output/", outputList);

    char inputFile[100] = {"config2016_100.csv\0"};
    char inputDir[100] = {"data/\0"};

    time_t begin;
    time_t end;
    createTimeFile();

    //main loop
    for (int i = 0; i<roughness->count; i++){
        changeParameter(roughness->name, roughness->array[i], inputFile, inputDir);
        
        for (int j = 0; j<elevation->count; j++){                                                                      //currently output folder
            char *args[] = {"./caflood", "-WCA2D", inputDir, inputFile, strcat(outputList[roughness->count*i+j], "/"), NULL};
            changeParameter(elevation->name, elevation->array[j], inputFile, inputDir);
            time(&begin);

            runCaflood(args);

            time(&end);
            printTime(begin, end, outputList[roughness->count*i+j]);
        }
    }

    return 0;
}