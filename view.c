#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

//Validate view func

int read_validate_view(MP3_Info *info, char *argv[])
{
    if(argv[1] == NULL || argv[2] == NULL)
    {
        printf("Error: Invalid Input\n");
        return 0;
    }

    if(strcmp(argv[1], "-v") != 0)
    {
        printf("Error: Invalid Operation\n");
        return 0;
    }

    if(strlen(argv[2]) < 4 ||
       strcmp(argv[2] + strlen(argv[2]) - 4, ".mp3") != 0)
    {
        printf("Error: File should be .mp3 file\n");
        return 0;
    }

    strcpy(info->filename, argv[2]);

    return 1;
}


// Display MP3 tag details

void do_view(MP3_Info *info)
{
    FILE *fptr;

    unsigned char header[10];
    unsigned char size_arr[4];
    unsigned char flag[3];

    char tag[5];
    char data[1000];

    int size;

    fptr = fopen(info->filename, "r");

    if(fptr == NULL)
    {
        printf("ERROR: Unable to open file\n");
        return;
    }


    // Read ID3 Header

    if(fread(header, 1, 10, fptr) != 10)
    {
        printf("ERROR: Invalid MP3 file\n");
        fclose(fptr);
        return;
    }

    printf("\n");
    printf("     .....MP3 TAG DETAILS....     \n");
    


    while(1)
    {
        // Read Frame ID

        if(fread(tag, 1, 4, fptr) != 4)
            break;

        tag[4] = '\0';


        // Read Frame Size

        if(fread(size_arr, 1, 4, fptr) != 4)
            break;

        size = cnvt(size_arr);

        if(size <= 0 || size >= 1000)
            break;


        // Read Flags and Encoding

        if(fread(flag, 1, 3, fptr) != 3)
            break;


        // Calculate remaining data size

        size = size - 1;

        if(size < 0)
            break;


        // Read Actual Tag Data

        if(fread(data, 1, size, fptr) != size)
            break;

        data[size] = '\0';


        // Print Required Information

        if(strcmp(tag, "TIT2") == 0)
        {
            printf("    Title   : %s\n", data);
        }
        else if(strcmp(tag, "TPE1") == 0)
        {
            printf("    Artist  : %s\n", data);
        }
        else if(strcmp(tag, "TALB") == 0)
        {
            printf("    Album   : %s\n", data);
        }
        else if(strcmp(tag, "TYER") == 0)
        {
            printf("    Year    : %s\n", data);
        }
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("    Comment : %s\n", data);
        }
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("    Genre   : %s\n", data);
        }
    }

    printf("\n");

    fclose(fptr);
}
