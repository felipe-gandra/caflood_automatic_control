# CAFlood Automatic Control
## Description

This repository is dedicated to the development of software that can automatically execute CAFlood multiple times while varying input parameters. This is part of my research project at the University of São Paulo.

![Flowchart](https://github.com/felipe-gandra/caflood_automatic_control/blob/main/images/flowchart.png?raw=true)

## How to Install and Run the Project

You can either download the executable file or compile the code on your own machine. After that, you should create a folder to store the outputs and input files. Execution is done via the terminal using the command:

```
./autocaflood <input folder dir> <input file> <parameter's file directory> <output folder dir>
``` 

The program assumes that the input file is located in the input folder.

The parameter file is a .csv file where you can specify all the parameter values that you want CAFlood to use. An example of this file can be found in the "Examples" folder. It is important to follow the same file format.

Currently, this program is capable of automatically executing CAFlood while varying the "Roughness Global" and "Elevation ASCII" parameters. If you want to modify it to work with other variables, there are instructions in the code indicating which functions may need adjustments.

#### Example Execution Line
```
./autocaflood input/ eat8a.csv Examples/data.csv output/
```

#### Compiling with Makefile
If you want to compile it in your machine, you can use Makefile like this:

```
all: functions.o main.o
	gcc functions.o main.o -Wall -o autocaflood

functions.o:
	gcc -c functions.c

main.o:
	gcc -c main.c
```

## Contact

If you need more information, feel free to email me at:

felipegandra2005@gmail.com 
felipegmoreira@usp.br




