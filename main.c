// Name                : Mohamed Fawaz.K.H
// Date                : 21/08/2026
// Project Name        : LSB Image Steganography
// Project Description : Developed a **console-based MP3 Tag Reader
//                       in C** to extract and display metadata such 
//                       as title, artist, album, year, and genre 
//                       from MP3 files.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

int main(int argc, char *argv[])
{
    MP3_Info info;
    int choice;

    choice = check_opr_type(argv);

    if(choice == 1)
    {
        if(read_validate_view(&info, argv) == 0)
            return 0;

        do_view(&info);
    }
    else if(choice == 2)
    {
        if(read_validate_edit(&info, argv) == 0)
            return 0;

        do_edit(&info);
    }
    else if(choice == 3)
    {
       help();
    }
    else
    {
        printf("Invalid Operation\n");
    }

    return 0;
}