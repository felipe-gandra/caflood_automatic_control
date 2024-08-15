#include "functions.h"
#include <stdio.h>

int main()
{   
    printf("0");

    Parameter *roughness = initParameter("Roughness Global");
    Parameter *elevation = initParameter("Elevation ASCII");

    printf("a");

    readData("dados.csv", roughness);
    readData("dados.csv", elevation);

    printf("b");

    char **outputList;
    int nOutputs = roughness->count * elevation->count;

    createOutputList(roughness, elevation, &outputList);

    printf("c");

    //createOutputFolders(nOutputs, "output/", outputList);

    printf("d");

    freeArray((void ***)&outputList, nOutputs);

    char newValue[100] = {"0.999"};
    char inputFile[100] = {"config2016_100.csv\0"};
    char inputDir[100] = {"data/\0"};

    changeParameter(roughness->name, roughness->array[5], inputFile, inputDir);
    changeParameter(elevation->name, elevation->array[1], inputFile, inputDir);

    return 0;
}