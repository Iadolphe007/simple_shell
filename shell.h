#ifndef SHELL_FILE
#define SHELL_FILE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <pwd.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 1024

char current_directory[BUFFER_SIZE];
extern char **environ;

/* Function declarations*/
char *get_command_path(char *command);
int string_compare(const char *str1, const char *str2);
void tokenize_command(char *command, char **argv, int max_args);
void execute_command(char *command_path, char **argv);
void execute_env_command(char **environ);
void comd(void);
void clear_screen(void);
void change_directory(char *path);
void handle_variable_replacement(char *command, int status);
int builtin_echo(char **args);
int exc_command(char *comd);
int my_strlen(const char *str);
char *my_strcpy(char *dest, char *src);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *user_getenv(const char *name);
int execute_exit_command(char *argv[]);
int execute_cd_command(char *argv[]);
int execute_echo_command(char *argv[]);
int execute_other_command(char *argv[]);
char *get_command_path(char *command);
char *get_absolute_command_path(char *command);
char *get_relative_command_path(char *command);


#endif
