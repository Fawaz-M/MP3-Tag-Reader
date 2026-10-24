#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
//validation for edit function


int read_validate_edit(MP3_Info *info, char *argv[])
{
    if(argv[1] == NULL)
    {
        printf("Invalid Arguments\n");
        return 0;
    }

    if(strcmp(argv[1], "-e") != 0)
    {
        printf("Invalid Operation\n");
        return 0;
    }

    if(argv[2] == NULL)
    {
        printf("Error: Edit option is missing\n");
        return 0;
    }

    if(strcmp(argv[2], "-t") == 0)
    {
        strcpy(info->target, "TIT2");
    }
    else if(strcmp(argv[2], "-a") == 0)
    {
        strcpy(info->target, "TPE1");
    }
    else if(strcmp(argv[2], "-A") == 0)
    {
        strcpy(info->target, "TALB");
    }
    else if(strcmp(argv[2], "-c") == 0)
    {
        strcpy(info->target, "COMM");
    }
    else if(strcmp(argv[2], "-g") == 0)
    {
        strcpy(info->target, "TCON");
    }
    else if(strcmp(argv[2], "-y") == 0)
    {
        strcpy(info->target, "TYER");
    }
    else
    {
        printf("ERROR: Invalid edit option\n");
        return 0;
    }

    if(argv[3] == NULL)
    {
        printf("Error: New Data is missing\n");
        return 0;
    }

    strcpy(info->new_data, argv[3]);

    if(argv[4] == NULL)
    {
        printf("Error: File name is missing\n");
        return 0;
    }

    if(strlen(argv[4]) < 4 ||
       strcmp(argv[4] + strlen(argv[4]) - 4, ".mp3") != 0)
    {
        printf("Error: File should be mp3 file\n");
        return 0;
    }

    strcpy(info->filename, argv[4]);

    return 1;
}

//edit operation starts
void do_edit(MP3_Info *info)
{
   FILE *fptr;
    FILE *temp;

    unsigned char header[10];
    unsigned char size_arr[4];
    unsigned char new_size_arr[4];
    unsigned char flag[3];

    char tag[5];
    char data[1000];
    char carry[1000];

    int size;
    int new_size;
    int much;
    int found = 0;


    // Open original MP3 file

    fptr = fopen(info->filename, "r");

    if(fptr == NULL)
    {
        printf("ERROR: Unable to open %s\n", info->filename);
        return;
    }


    // Create temporary file

    temp = fopen("temp.mp3", "w");

    if(temp == NULL)
    {
        printf("ERROR: Unable to create temp.mp3\n");
        fclose(fptr);
        return;
    }


    // Read ID3 Header

    if(fread(header, 1, 10, fptr) != 10)
    {
        printf("ERROR: Invalid MP3 file\n");

        fclose(fptr);
        fclose(temp);

        remove("temp.mp3");

        return;
    }


    // Copy Header

    fwrite(header, 1, 10, temp);


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


        // Validate frame size

        if(size <= 0 || size >= 1000)
            break;


        // Read Flags and Encoding

        if(fread(flag, 1, 3, fptr) != 3)
            break;


        // Read frame data

        size = size - 1;

        if(size < 0)
            break;

        if(fread(data, 1, size, fptr) != size)
            break;


        // Check selected tag

        if(strcmp(tag, info->target) == 0)
        {
            found = 1;

            printf("\n%s tag found\n", tag);


            // Calculate new frame size

            new_size = strlen(info->new_data) + 1;


            // Convert size to Big Endian

            bgen(new_size, new_size_arr);


            // Write Frame ID

            fwrite(tag, 1, 4, temp);


            // Write new frame size

            fwrite(new_size_arr, 1, 4, temp);


            // Write flags and encoding

            fwrite(flag, 1, 3, temp);


            // Write new data

            fwrite(info->new_data,
                   1,
                   strlen(info->new_data),
                   temp);


            // Copy remaining MP3 data

            while((much = fread(carry, 1, 1000, fptr)) > 0)
            {
                fwrite(carry, 1, much, temp);
            }

            break;
        }
        else
        {
            // Copy original frame

            fwrite(tag, 1, 4, temp);

            fwrite(size_arr, 1, 4, temp);

            fwrite(flag, 1, 3, temp);

            fwrite(data, 1, size, temp);
        }
    }


    fclose(fptr);
    fclose(temp);


    // Check selected tag found

    if(found == 0)
    {
        printf("ERROR: Tag not found\n");

        remove("temp.mp3");

        return;
    }


    // Delete original file

    remove(info->filename);


    // Rename temporary file

    rename("temp.mp3", info->filename);


    printf("\nTag        : %s\n", info->target);
    printf("New Data   : %s\n", info->new_data);
    printf("File       : %s\n", info->filename);

    printf("\n!!!...Tag Edition Completed...!!!\n\n");
}