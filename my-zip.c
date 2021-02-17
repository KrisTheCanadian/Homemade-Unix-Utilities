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
            printf("my-zip: cannot open file \n");
            return 1;
        }

        char* line_buf = NULL;
        size_t line_buf_size = 0;
        ssize_t line_size = getline(&line_buf, &line_buf_size, fp);
        int line_count;

        char* sp = line_buf;
        char* ch;
        int count = 0;

        while(line_size >= 0)
        {
            line_count++;

            do
            {
                if(isalpha(*sp))
                {
                    if(*sp == *ch)
                    {
                        ++count;
                    }
                    if(*sp != *ch || *(sp+1) == '\0')
                    {
                        if(count < 1)
                        {
                            ch = sp;
                            ++count;
                        }
                        else
                        {
                            fwrite(&count, sizeof(int), 1, stdout);
                            fwrite(ch, sizeof(char), 1, stdout);
                            count = 1;
                            ch = sp;
                        }
                    }
                }
                ++sp;
            }while(*sp != '\0');

            line_size = getline(&line_buf, &line_buf_size, fp);
        }
        free(line_buf);
        line_buf = NULL;
        fclose(fp);
    }
    return 0;
}