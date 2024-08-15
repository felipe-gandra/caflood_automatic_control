#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    typedef struct PARAMETER Parameter;

    void initParameter(Parameter * parameter, char * parameterName);

    void saveValues(Parameter * parameter);

    void readData(char *fileName, Parameter * parameter);

    void createOutputList(Parameter * Roughness, Parameter *Elevation, char ** outputList);

    void createOutputFolders(int nOutputs, char * outputFolder, char ** outputList);

    void printTime(int begin, int end, char *name);

    void createTimeFile(void);

    void freeArray(void **array, int n);
#endif