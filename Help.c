#include <stdio.h>
#include "mp3.h"

void help(void)
{
    printf("Help Option For MP3 Tag Reader\n\n");
    printf("\nVIEW OPTION:\n");
    printf("-v filename.mp3\n");

    printf("\nEDIT OPTION:\n");
    printf("-e -? filename.mp3\n\n");
    
    printf("-t to edit Title Tag\n");
    printf("-a to edit Album Tag\n");
    printf("-A to edit Artist Tag\n");
    printf("-g to edit Genre Tag\n");
    printf("-y to edit Year Tag\n");
    printf("-c to edit Comment Tag\n");

    printf("\nHELP OPTION:\n");
    printf("-h\n\n");
}