#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    typedef struct PARAMETER{
        char name[20];
        char ** array;
        int count;
    }Parameter;

    Parameter * initParameter(char * parameterName);

    void saveValues(Parameter * parameter);

    void readData(char *fileName, Parameter * parameter);

    void createOutputList(Parameter * Roughness, Parameter *Elevation, char *** outputList);

    void createOutputFolders(int nOutputs, char * outputFolder, char ** outputList);

    void printTime(int begin, int end, char *name);

    void createTimeFile(void);

    void freeArray(void ***array, int n);

    void changeParameter(char * parameterName, char * newValue, char * inputFile, char * inputDir);

    void runCaflood(char ** args);
#endif