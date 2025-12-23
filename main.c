#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This is the function to read the line */

char* read_line(){
    int buffersize = 1024;
    int position = 0;

    char* buffer = malloc(sizeof(char)*buffersize);
    int c;

    if(!buffer){
        printf("\nAllocation of memory failed\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        c = getchar();
        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            break;
        }else{
            buffer[position] = c;
        }
    }
    position++;

    if(position >= buffersize){
        buffersize += 10224;
        buffer = realloc(buffer, buffersize);

        if(!buffer){
            printf("\nAllocation of memory failed\n");
            exit(EXIT_FAILURE);
        }
    }

    return buffer;
}

/* This is the function to tokenize the inputted line */

char** get_args(char* line){
    int buffersize = 1024;
    int position = 0;

    char** tokens = malloc(buffersize * sizeof(char *));
    if(!tokens){
        printf("\nAllocation of memory failed\n");
        exit(EXIT_FAILURE);
    }

    char* token;
    token = strtok(line, " ");

    while(token){
        tokens[position] = token;
        position++;

        if(position >= buffersize){
            buffersize += 1024;
            tokens = realloc(tokens, buffersize);

            if(!tokens){
                printf("\nAllocation of memory failed\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }

    return tokens;
}

int exec(char** args){
    return 1;
}

/* The main loop lies here. This is the part which continuously works*/

void loop(){
    char* line;
    char** args;
    int status = 1;

    do {
        printf("> ");
        line = read_line();
        args = get_args(line);
        status = exec(args);
        free(line);
        free(args);
    }while(status);
}

/* Main function */

int main(){
    loop();
    return 0;
}