#ifndef FUNCTIONS_H
    #define FUNCTIONS_H


    /*
    -Struct to keep information about the parameters that the user wants to change.

    -name: parameter's name.
    -array: array of strings containing the values.
    -count: number of values in the array.  */
    typedef struct PARAMETER{
        char name[20];
        char ** array;
        int count;
    }Parameter;

    /*
    -Initializes a parameter. Allocate memory and assign a name.

    -parameterName: string containing the parameter's name.  */
    Parameter * initParameter(char * parameterName);

    /*
    -Function to save all values, separated by ' ,', in the parameter's array.

    -parameter: parameter's struct where the values are going to be saved.   */
    void saveValues(Parameter * parameter);

    /*
    -Reads all values in a data.csv file. Save all those values in the array using
    saveValues function.

    -filename: string containing the name of the file with parameter's values.
    -parameter: parameter's struct where the values are going to be saved.  */
    void readData(char *fileName, Parameter * parameter);

    /*
    -Creates an array of string containing for each combination of parameters.

    -Roughness: struct containing the information about roughness global.
    -Elevation: struct containing the information about elevation ascii.
    -outputList: the adress of the array with the list of outputs.
    
    ps: if the user wants to use this with another parameter, the function can be easily changed. */
    void createOutputList(Parameter * Roughness, Parameter *Elevation, char *** outputList);

    /*
    -Creates an output folder for each combination of parameter's values. 

    -nOutputs: number of combinatios, i. e. number of outputs.
    -outputFolder: string containing the output directory.
    -outputList: string array containing the name of each output.   */
    void createOutputFolders(int nOutputs, char * outputFolder, char ** outputList);

    /*
    -Prints the time took for each execution in a 'time.txt' file.

    -begin: time when the execution began.
    -end: time when the execution ended.
    -name: string containing the simulation name.  */
    void printTime(int begin, int end, char *name);

    /*
    -Creates the file to keep the time took for each simulation.*/
    void createTimeFile(void);

    /*
    -Free an bidimentional array with n columns*/
    void freeArray(void ***array, int n);
    
    /*
    -Changes the parameter's value in the input.csv file. 

    -parameterName: string containing the parameter's name.
    -newValue: new parameter's name.
    -inputFile: string containing the name of the input.csv file.
    -inputDir: string containing the input folder directory.    */
    void changeParameter(char * parameterName, char * newValue, char * inputFile, char * inputDir);

    /*
    -Function to run caflood with proper args.

    -args: list of arguments.*/
    void runCaflood(char ** args);
#endif