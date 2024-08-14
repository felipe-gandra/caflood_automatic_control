#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>


typedef struct DATA{
    char name[20];
    char ** array;
    int count;
}Data;

int freeArray(void **array, int n)
{
    if (array == NULL)
    {
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        if (array[i] != NULL)
        {
            free(array[i]);
            array[i] = NULL;
        }
    }
    free(array);
    array = NULL;
    return 0;
}