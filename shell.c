#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// -----------------------------------------------------------------------------
// Built in commands.
// -----------------------------------------------------------------------------

void shell_exit(char **args) {
    exit(0);
}

void shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "shell: cd: missing argument\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("shell: cd");
        }
    }
}
void shell_echo(char **args)
{	    if (args[1] == NULL) {
        printf("\n");
    } else {
	for(int i =1; i<1024; i++){
	if(args[i] == NULL){
	printf("\n");
	i = 1024;
	}else{
	printf("%s ", args[i]);}}
}
}
void shell_pwd()
{
	char* pwd = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++){
	pwd[i] = '\0';
	}
	getcwd(pwd,1024);
	printf("%s\n",pwd);
}

void shell_help(char **args) {
    char *helptext =
        "  Shell  "
        "The following commands are built in:\n"
        "  cd       Change the working directory.\n"
        "  exit     Exit the shell.\n"
        "  help     Print this help text.\n"
        "  echo     Print any text.\n"
        "  pwd      Path of present working directory.\n"
        ;
    printf("%s", helptext);
}
void shell_ls(char **args){
	execvp(args[0], args);
	perror("shell");
    exit(1);
}
void shell_date(char **args){
    execvp(args[0], args);
    perror("shell");
    exit(1);
    }
void shell_rm(char **args){
	execvp(args[0], args);
    perror("shell");
    exit(1);
}
void shell_cat(char **args){
    execvp(args[0], args);
	perror("shell");
    exit(1);
}
void shell_mkdir(char **args){
    execvp(args[0], args);
    perror("shell");
    exit(1);
}

struct builtin {
    char *name;
    void (*func)(char **args);
};
struct external {
    char *name;
    void (*func)(char **args);
};
// Array of built in commands.
struct builtin builtins[] = {
    {"help", shell_help},
    {"exit", shell_exit},
    {"cd", shell_cd},
    {"pwd", shell_pwd},
    {"echo", shell_echo},
    
};

struct external externals[] = {
    {"ls", shell_ls},
    {"date", shell_date},
    {"mkdir", shell_mkdir},
    {"cat", shell_cat},
    {"rm", shell_rm},
    
};
int shell_num_builtins() {
    return sizeof(builtins) / sizeof(struct builtin);
}
int shell_num_externals() {
    return sizeof(externals) / sizeof(struct external);
}
void shell_exec(char **args) {
    for (int i = 0; i < shell_num_builtins(); i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            builtins[i].func(args);
            return;
        }
    }

    pid_t child_pid = fork();

    if (child_pid == 0) {
        //execvp(args[0], args);
        for (int j = 0; j < shell_num_externals(); j++) {
        if (strcmp(args[0], externals[j].name) == 0) {
            externals[j].func(args);
            return;
        }
        }

     }else if (child_pid > 0) {
        int status;
        do {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        perror("shell");
    }
}

char** shell_split_line(char *line) {
    int length = 0;
    int capacity = 1024;

    char **tokens = malloc(capacity * sizeof(char*));
    if (!tokens) {
        perror("shell");
        exit(1);
    }

    char *delimiters = " \t\r\n";
    char *token = strtok(line, delimiters);

    while (token != NULL) {
        tokens[length] = token;
        length++;

        if (length >= capacity) {
            capacity = (int) (capacity * 1.5);
            tokens = realloc(tokens, capacity * sizeof(char*));
            if (!tokens) {
                perror("shell");
                exit(1);
            }
        }

        token = strtok(NULL, delimiters);
    }

    tokens[length] = NULL;
    return tokens;
}

char* shell_read_line() {
    char *line = NULL;
    size_t buflen = 0;
    errno = 0;
    ssize_t strlen = getline(&line, &buflen, stdin);
    if (strlen < 0) {
        if (errno) {
            perror("shell");
        }
        exit(1);
    }
    return line;
}

// -----------------------------------------------------------------------------
// Entry point.
// -----------------------------------------------------------------------------

int main() {
    while (true) {
        printf("> ");
        char *line = shell_read_line();
        char **tokens = shell_split_line(line);

        if (tokens[0] != NULL) {
            shell_exec(tokens);
        }

        free(tokens);
        free(line);
    }
}
