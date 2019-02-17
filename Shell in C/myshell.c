//
//  main.c
//  Copyright © 2016 Zeeshaan Manji. All rights reserved.

// ZEESHAAN MANJI //
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


#define BUFSIZE 100
#define TOKEN_BUFSIZE 64
#define TOKEN_DEL " \t\r\n\a"

// FUNCTION DECLARATIONS

int cd(char **a);
int exit1(char **a);
///
// THESE ARE THE BUILT IN FUNCTIONS
char *storage_strings[] = {
    "cd",
    "exit"
};

int (*functions[]) (char **) = {
    &cd,
    &exit1
};

int builtin() { // size of the storage strings which is 2
    return sizeof(storage_strings) / sizeof(char *);
}


int cd(char **args) // WHEN YOU USE THE CD FUNCTION IN TERMINAL IT GOES THROUGH THIS FUNCTION
{
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}



int exit1(char **a) // THIS IS AN EXIT FUNCTION TO TERMINATE THE SHELL
{
    return 0;
}


int launch(char **a)
{
    pid_t pid_11;
    int status;
    
    pid_11 = fork();
    if (pid_11 == 0) {
        if (execvp(a[0], a) == -1) { // THIS IS THE CHILD PROCESS  ( USED THE EXECVP FUNCTION HERE)
            perror("ERROR");
        }
        exit(1);
    } else if (pid_11 < 0) {
        perror("ERROR FORKING"); // IF WE HAVE AN ERROR FORKING
    } else { // THIS IS THE PARENT PROCESS
         do {
            waitpid(pid_11, &status, WUNTRACED);       // USED THE WAITPID FUNCTION HERE
       
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return 1;
}


int run(char **a)
{
   
    int i;
    
    if (a[0] == NULL) {
        // An empty command was entered.
        return 1;
    }
    
    for (i = 0; i < builtin(); i++) {
        if (strcmp(a[0], storage_strings[i]) == 0)
        {
            
            return (*functions[i])(a);
        }
    }
   

    return launch(a);
}



 char *readline(void )
{
    int bufsize = BUFSIZE;
    int index = 0;
    char *buffer = malloc(sizeof(char*) * bufsize);
    int c;
    
    if (!buffer) {
        fprintf(stderr, "lsh: ERROR: ALLOCATION ERROR \n");
        exit(1);
    }
    
    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {  // THIS PART IS TO CHECK THE END OF THE FILE
            buffer[index] = '\0';
            return buffer;
        } else {
            buffer[index] = c;
        }
        index++;

        if (index >= bufsize) {  // THIS PART IS INCASE IF WE EXCEED THE BUFFER WE INCREASE THE SIZE HERE
            bufsize += BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "ERROR:  ALLOCATION ERROR\n");
                exit(1);
            }
        }
    }
}



char **splitline(char *line)  // THIS FUNCTION BASICALLY SPLITS THE LINE INTO TOKENS SO IT IS EASIER TO PROCESS
{
   
    int index=0;
    char *tok, **tok_back;
    int buf = TOKEN_BUFSIZE;
     char **token = malloc(buf * sizeof(char*));
 
    
    if (!token) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    tok = strtok(line, TOKEN_DEL);
    while (tok != NULL) {
        token[index] = tok;
        index++;
        
        if (index >= buf) {
            buf += TOKEN_BUFSIZE;
            tok_back = token;
            token = realloc(token, buf * sizeof(char*));
            if (!token) {
                free(tok_back);
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        tok = strtok(NULL, TOKEN_DEL);
    }
    token[index] = NULL;
    
  
    return token;

}





int main()
{
    printf("ASSIGNMENT 1 SHELL CMPT 300 \n");

    
    int status_UPDATE;
    char *lineread;
    char **argument;
    
    
    do {
        time_t terminaltimer;
        char buff[26];
        struct tim* tm_info;
        time(&terminaltimer);
        tm_info=localtime(&terminaltimer);
        strftime(buff, 26, "%H:%M:%S# ", tm_info);
        printf(buff);
        lineread = readline();
        if (strcmp(lineread,"exit")==1)
        {
            exit1(lineread);
        }
        else
        {
        argument = splitline(lineread);
        status_UPDATE =run(argument);
        }
        //free(lineread);
        //free(argument);
    } while (status_UPDATE);



    return 0;
}
