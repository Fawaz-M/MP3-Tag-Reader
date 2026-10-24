#include <stdio.h>
#include "mp3.h"

int cnvt(unsigned char *size)
{
    return ((size[0] << 24) |
            (size[1] << 16) |
            (size[2] << 8) |
             size[3]);
}

void bgen(int size, unsigned char *arr)
{
    arr[0] = (size >> 24) & 0xFF;
    arr[1] = (size >> 16) & 0xFF;
    arr[2] = (size >> 8) & 0xFF;
    arr[3] = size & 0xFF;
}