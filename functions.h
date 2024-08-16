#ifndef FUNCTIONS_H
    #define FUNCTIONS_H


    /*
    Struct to keep information about the parameters that the user wants to change.
    name: parameter's name
    array: array of strings containing the values
    count: number of values in the array  */
    typedef struct PARAMETER{
        char name[20];
        char ** array;
        int count;
    }Parameter;

    /*
    Initializes a parameter. Allocate memory and assign a name.
    Receives a string containing the parameter's name  */
    Parameter * initParameter(char * parameterName);

    /*
    Function to save all values, separated by ' ,', in the parameter's array.
    Receives the parameter's struct. */
    void saveValues(Parameter * parameter);

    /*
    Reads all values in a data.csv file. Save all those values in the array using
    saveValues function.
    Receives the name of the file and the parameter's struct.  */
    void readData(char *fileName, Parameter * parameter);

    /*
    Creates an array of string containing for each combination of parameters.
    Receives the struct of Roughness Global, the struct of Elevation ASCII and the adress of the 
    array with the list of outpus.
    
    ps: if the user wants to use this with another parameter, the function can be easily changed. */
    void createOutputList(Parameter * Roughness, Parameter *Elevation, char *** outputList);

    /*
    Creates an output folder for each combination of parameter's values. 
    Receives the number of combinations, the name of the output folder and the list of outputs.  */
    void createOutputFolders(int nOutputs, char * outputFolder, char ** outputList);

    /*
    Prints the time took for each execution in a 'time.txt' file.
    Receives the time when the execution began and ended, the name of the simulation.  */
    void printTime(int begin, int end, char *name);

    /*
    Creates the file to keep the time took for each simulation.*/
    void createTimeFile(void);

    /*
    Free an bidimentional array with n columns*/
    void freeArray(void ***array, int n);
    
    /*
    Changes the parameter's value in the input.csv file. 
    Receives the parameter's name, the new value, the name of the input.csv file
     and the input folder directory*/
    void changeParameter(char * parameterName, char * newValue, char * inputFile, char * inputDir);

    /*
    Function to run caflood with proper args.
    Receives an list of arguments.*/
    void runCaflood(char ** args);
#endif