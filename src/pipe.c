/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:58:20 by quackson          #+#    #+#             */
/*   Updated: 2023/06/14 01:16:56 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

// herdoc -> escrevmos as cenas -> close() redirect_input(temp) executamos -> unlink(temp)

void restore_stdout(void)
{
	int terminal_fd = open("/dev/tty", O_RDWR);
	if (terminal_fd < 0)
	{
		perror("open failed");
		exit(1);
	}
	dup2(terminal_fd, STDOUT_FILENO);
	close(terminal_fd);
}

void	restore_stdin(void)
{
	int	terminal_fd;

	terminal_fd = open("/dev/tty", O_RDWR);
	if (terminal_fd < 0)
	{
		perror("open failed");
	}
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
}

void	heredoc(char *delimiter)
{
	if (delimiter != NULL)
	{
		restore_stdin();

		char temp_file[] = "/tmp/tempfileXXXXXX";
		// Create a temporary file
		int temp_fd = mkstemp(temp_file);
		if (temp_fd < 0)
		{
			perror("mkstemp failed");
			exit(1);
		}

		// Write input to the temporary file until the delimiter is found
		char* line = NULL;
		int found_delimiter = 0;

		while (!found_delimiter)
		{
			line = readline("heredoc> ");
			if (line == NULL)
			{
				perror("get_next_line failed");
				exit(1);
			}
			if (line == NULL)
			{
				perror("get_next_line failed");
				exit(1);
			}
			if (strcmp(line, delimiter) == 0)
			{
				found_delimiter = 1;
				//get_next_line(-1);
			}
			else
			{
				write(temp_fd, line, strlen(line));
				write(temp_fd, "\n", 1);
			}
			free(line);
		}

		// Close the temporary file
		close(temp_fd);

		// redirec_input(temp_file)
		// exe_cmd
		// unlink()
		// Reopen the temporary file for reading
		temp_fd = open(temp_file, O_RDONLY);
		if (temp_fd < 0)
		{
			perror("open failed");
			exit(1);
		}

		// Set the temporary file as input for the command
		dup2(temp_fd, STDIN_FILENO);
		close(temp_fd);

		// Remove the temporary file
		unlink(temp_file);
	}
}

void redirect_input(char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		fprintf(stderr, "file: %s\n", file);
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
		fprintf(stderr, "file: %s\n", file);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

t_input	*get_next_cmd(t_input *input)
{
	while (input)
	{
		if (!ft_strncmp(input->token, "|", 1) && !input->within_quotes)
			return (input->next);
		input = input->next;
	}
	return (input);
}

int	count_tokens_str(char **args)
{
	int		i;

	i = 0;
	while (*args)
	{
		args++;
		i++;
	}
	return (i);
}

int	count_tokens_lst(t_input *input)
{
	int	num_tokens;

	num_tokens = 0;
	while (input && !ft_strncmp(input->token, "|", 1) && !input->within_quotes)
	{
		if (is_redirection(input->token) && !input->within_quotes)
			return (num_tokens);
		input = input->next;
		//print_list(minishell->input);
	}
	return (num_tokens);
}

void	print_command(char **args, int n_tokens)
{
	int	i;

	i = 0;
	while (args[i] && n_tokens--)
	{
		//printf("%s ", args[i]);
		i++;
	}
	//printf("\n");
}

char	*get_next_redirection(char **args)
{
	while (*args)
	{
		if (is_redirection(*args))
			return (*args);
		args++;
	}
	return (NULL);
}

int	cmd_has_pipe(char **args)
{
	while (*args)
	{
		if (!strncmp(*args, "|", 1))
			return (1);
		args++;
	}
	return (0);
}

int	count_commands_lst(t_input *input)
{
	int	n_commands;

	n_commands = 0;
	while (input)
	{
		if (!ft_strncmp(input->token, "|", 1) && !input->within_quotes)
			n_commands++;
		input = input->next;
	}
	return (n_commands + 1);
}

int	count_arguments(t_input *input)
{
	int		num_args;
	int		redirect_flag;

	num_args = 0;
	redirect_flag = 0;
	while (input && !(!ft_strncmp(input->token, "|", 1) && !input->within_quotes))
	{
		if (redirect_flag)
			redirect_flag = 0;
		else if (is_redirection(input->token) && !input->within_quotes)
			redirect_flag = 1;
		else
			num_args++;
		input = input->next;
	}
	return (num_args);
}

char	**get_command_without_redirects(t_input *input)
{
	char	**command;
	int		num_args;
	int		redirect_flag;
	int		i;

	num_args = count_arguments(input);
	command = malloc(sizeof(char *) * (num_args + 1));
	if (!command)
		return (NULL);
	redirect_flag = 0;
	i = 0;
	while (input && !(!ft_strncmp(input->token, "|", 1) && !input->within_quotes))
	{
		if (redirect_flag)
			redirect_flag = 0;
		else if (is_redirection(input->token) && !input->within_quotes)
			redirect_flag = 1;
		else
		{
			command[i++] = ft_strdup(input->token);
			if (!command[i - 1])
				return (NULL);
		}
		input = input->next;
	}
	command[i] = NULL;
	return (command);
}

void	handle_redirections(t_input *input)
{
	char	*file;

	while (input && !(!ft_strncmp(input->token, "|", 1) && !input->within_quotes))
	{
		if (!ft_strncmp(input->token, "<<", 2) && !input->within_quotes)
		{
			file = input->next->token;
			heredoc(file);
		}
		else if (!ft_strncmp(input->token, "<", 1) && !input->within_quotes)
		{
			file = input->next->token;
			redirect_input(file);
		}
		else if (!ft_strncmp(input->token, ">>", 2) && !input->within_quotes)
		{
			file = input->next->token;
			redirect_output(file, 1);
		}
		else if (!ft_strncmp(input->token, ">", 1) && !input->within_quotes)
		{
			file = input->next->token;
			redirect_output(file, 0);
		}
		input = input->next;
	}
}

// echo hello > file.txt | cat file.txt
// "echo", "hello", NULL
void redirect_3(t_input *input, int num_commands, t_minishell *minishell)
{
	int pipe_fd[2];  // Pipe file descriptors
	int in_fd = 0;   // Input file descriptor for the first command
	char **cmds;
	int status;

	cmds = NULL;
	(void) minishell;
	for (int i = 0; i < num_commands; i++)
	{
		if (i < num_commands - 1) {
			if (pipe(pipe_fd) < 0) {
				perror("pipe failed");
				exit(1);
			}
		}
		/* for (int j = 0; cmds[j]; j++)
			printf("cmd: %s\n", cmds[j]);
		printf("----\n"); */
		pid_t pid = fork();
		if (pid < 0) {
			perror("fork failed");
			exit(1);
		} else if (pid == 0)
		{
			// Redirect input from the previous command or file
			cmds = get_command_without_redirects(input);
			if (i != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			// Redirect output to the next command or file
			if (i < num_commands - 1)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			handle_redirections(input);
			if (exe_cmd(cmds, count_tokens_str(cmds), minishell) == -1)
				exe_shell_cmd(cmds, count_tokens_str(cmds));
			free_parsed(cmds);
			//free_input_resources(minishell);
			free_minishell(minishell);
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent process
			// Close the previous pipe's write end
			if (i > 0)
			{
				close(in_fd);
			}
			// Close the current pipe's read end
			if (i < num_commands - 1)
			{
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
		}
		input = get_next_cmd(input);
	}
	while (num_commands > 0)
	{
		wait(&status);
		minishell->exit_status = WEXITSTATUS(status);
		num_commands--;
	}
}

void	save_fds(t_minishell *minishell)
{
	minishell->in = dup(STDIN_FILENO);
	minishell->out = dup(STDOUT_FILENO);
}

void	reset_fds(t_minishell *minishell)
{
	dup2(minishell->in, STDIN_FILENO);
	dup2(minishell->out, STDOUT_FILENO);
	close(minishell->in);
	close(minishell->out);
}

int	exe_commands(t_minishell *minishell)
{
	int		num_commands;
	int		status;
	char	**tokens;

	num_commands = count_commands_lst(minishell->input);
	if (num_commands > 1)
		redirect_3(minishell->input, num_commands, minishell);
	if (num_commands == 1)
	{
		tokens = get_command_without_redirects(minishell->input);
		if (!tokens)
		{
			free_minishell(minishell);
			exit(EXIT_SUCCESS);
		}
		if (!tokens[0])
		{
			save_fds(minishell);
			handle_redirections(minishell->input);
			reset_fds(minishell);
		}
		else if (is_builtin(tokens))
		{
			save_fds(minishell);
			handle_redirections(minishell->input);
			status = exe_cmd(tokens, count_tokens_str(tokens),
					minishell);
			reset_fds(minishell);
			if (status == EXIT)
			{
				free_minishell(minishell);
				printf("exit\n");
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			redirect_3(minishell->input, num_commands, minishell);
		}
		free_parsed(tokens);
	}
	return (NO_EXIT);
}
