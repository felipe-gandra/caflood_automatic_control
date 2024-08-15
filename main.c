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

    createOutputFolders(nOutputs, "output/", outputList);

    printf("d");

    freeArray((void ***)&outputList, nOutputs);

    return 0;
}