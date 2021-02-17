#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE (512)

int main(int argc, char *argv[])
{
    int count = 0;

    while(argv[++count])
    {
        FILE *fp = fopen(argv[count], "r");
        if(fp == NULL)
        {
            printf("my-unzip: cannot open file \n");
            return 1;
        }

        int index = 0;
        int isChar = 0;
        int number = 0;
        char letter = 'a';
        while (1)
        {
            isChar = index % 2;
            if (!isChar)
            {
                if (fread(&number, sizeof(int), 1, fp) == 0) break;
                printf("%d", number);
            }
            else
            {
                if (fread(&letter, sizeof(char), 1, fp) == 0) break;
                printf("%c", letter);
            }

            index++;
        }

        fclose(fp);
    }
    
    return 0;
}