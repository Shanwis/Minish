#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFERSIZE 1024

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
            buffer[position++] = '\0';
            break;
        }else{
            buffer[position++] = c;
        }

        if(position >= buffersize){
            buffersize += 1024;
            buffer = realloc(buffer, buffersize * sizeof(char));

            if(!buffer){
                printf("\nAllocation of memory failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return buffer;
}

/* This is the function to tokenize the inputted line */

char** get_args(char *line){
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
            tokens = realloc(tokens, buffersize * sizeof(char));

            if(!tokens){
                printf("\nAllocation of memory failed\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }
    tokens[position] = NULL;
    return tokens;
}

/* To exit the shell */

int exit_shell(char **args){
    return 0;
}

/* This is the function which actually executes the commands */

int exec(char **args){

    if(args[0] == NULL) return -1;

    if(strcmp(args[0],"exit") == 0){
        return exit_shell(args);
    }

    pid_t cpid = fork();
    int status;

    if(cpid == 0){
        if(execvp(args[0],args) < 0){
            printf("minish: command not found: %s\n",args[0]);
        }
        exit(EXIT_FAILURE);
    } else if(cpid < 0){
        printf("Forking failed\n");
    } else {
        waitpid(cpid, &status, WUNTRACED);
    }

    return 1;
}

/* The main loop lies here. This is the part which continuously works*/

void loop(){
    char *line;
    char **args;
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