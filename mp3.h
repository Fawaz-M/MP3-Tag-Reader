#ifndef MP3_H
#define MP3_H
//structure //
typedef struct
{
    char filename[100];
    char target[5];
    char new_data[1000];

} MP3_Info;

int read_validate_view(MP3_Info *info, char *argv[]);
void do_view(MP3_Info *info);
int read_validate_edit(MP3_Info *info, char *argv[]);
void do_edit(MP3_Info *info);
int cnvt(unsigned char *size);
void bgen(int size, unsigned char *arr);
int check_opr_type(char *argv[]);
void help(void);
#endif