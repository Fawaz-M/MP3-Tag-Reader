#include <stdio.h>
#include <string.h>
#include "mp3.h"

int check_opr_type(char *argv[])
{
    if(argv[1] == NULL)
    {
        return 0;
    }

    if(strcmp(argv[1], "-v") == 0)
    {
        return 1;
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        return 2;
    }
    else if(strcmp(argv[1], "-h") == 0)
    {
        return 3;
    }

    return 0;
}