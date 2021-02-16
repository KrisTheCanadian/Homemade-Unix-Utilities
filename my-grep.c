#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (512)

int main(int argc, char *argv[])
{
    if(!argv[1] && !argv[2]){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    char* searchterm = argv[1];

    int count = 1;

    if(argv[2] == NULL){
        char string[BUFFER_SIZE];
        fgets(string, BUFFER_SIZE, stdin);
        if(strstr(string, searchterm) != NULL){
            printf("%s", string);
        }
        return 0;
    }

    while(argv[++count])
    {
        FILE *fp = fopen(argv[count], "r");
        if(fp == NULL)
        {
            printf("my-grep: cannot open file \n");
            return 1;
        }

        char* line_buf = NULL;
        size_t line_buf_size = 0;
        ssize_t line_size = getline(&line_buf, &line_buf_size, fp);
        int line_count;

        
        while(line_size >= 0)
        {
            line_count++;
            if(strstr(line_buf, searchterm) != NULL)
            {
                printf("%s", line_buf);
            }

            line_size = getline(&line_buf, &line_buf_size, fp);
        }
        free(line_buf);
        line_buf = NULL;
        fclose(fp);
    }
    return 0;
}