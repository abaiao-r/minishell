#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
    char    *str;
    size_t  i;
    size_t  j;

    str = (char *)malloc(sizeof(*s1) * (strlen(s1) + strlen(s2) + 1));
    if (!str)
    {
        return (NULL);
    }
    i = 0;
    j = 0;
    while (s1[i])
    {
        str[j++] = s1[i];
        i++;
    }
    i = 0;
    while (s2[i])
    {
        str[j++] = s2[i];
        i++;
    }
    str[j] = '\0';
    return (str);
}

void redirect_input(char* file)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void redirect_output(char* file, int append)
{
    int flags = O_WRONLY | O_CREAT;

    if (append)
    {
        flags |= O_APPEND;
    }
    else
    {
        flags |= O_TRUNC;
    }
    int fd = open(file, flags, 0666);
    if (fd < 0)
    {
        perror("open failed");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

int main(void)
{
    char input[1000];
    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char* command = strtok(input, " ");

    char* arguments[100];
    int arg_count = 0;

    while (command != NULL)
    {
        if (strcmp(command, "<") == 0)
        {
            char* file = strtok(NULL, " ");
            redirect_input(file);
        } 
        else if (strcmp(command, ">") == 0)
        {
            char* file = strtok(NULL, " ");
            redirect_output(file, 0);
        } 
        else if (strcmp(command, ">>") == 0)
        {
            char* file = strtok(NULL, " ");
            redirect_output(file, 1);
        }
        else
        {
            arguments[arg_count++] = command;
        }
        command = strtok(NULL, " ");
    }

    arguments[arg_count] = NULL; // Set last argument to NULL for execve

    // Get the executable path from the PATH environment variable
    char* path = getenv("PATH");
    char* path_copy = strdup(path);
    char* path_token = strtok(path_copy, ":");

    while (path_token != NULL)
    {
        char* executable_path = ft_strjoin(path_token, "/");
        executable_path = ft_strjoin(executable_path, arguments[0]);
        if (access(executable_path, X_OK) == 0)
            execve(executable_path, arguments, NULL);
        free(executable_path);

        path_token = strtok(NULL, ":");
    }

    perror("execve failed");
    exit(1);
}