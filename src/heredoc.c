/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:42:49 by quackson          #+#    #+#             */
/*   Updated: 2023/06/24 18:41:21 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* restore_stdin: restores the standard input.
It opens the terminal file, duplicates the file descriptor
and closes the terminal file. */
static void	restore_stdin(void)
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

/* write_line: writes the line to the temporary file.
If the line is equal to the delimiter, it frees the line and returns 1.
Otherwise, it writes the line to the temporary file and returns 0. */
static int	write_line(char *delimiter, int temp_fd)
{
	char	*line;

	line = readline("heredoc> ");
	if (line == NULL)
	{
		ft_putstr_fd(
			"heredoc: warning: here-document delimited by end-of-file ",
			STDERR_FILENO);
		ft_putstr_fd("(wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("\')\n", STDERR_FILENO);
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	else
	{
		write(temp_fd, line, ft_strlen(line));
		write(temp_fd, "\n", 1);
	}
	free(line);
	return (0);
}

/* change_terminal: changes the terminal settings.
It gets the terminal settings, disables the quit character
and sets the terminal settings. */
static void	change_terminal(void)
{
	struct termios	term_settings;

	tcgetattr(STDIN_FILENO, &term_settings);
	term_settings.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

/* heredoc_child: changes the terminal settings, redirects the input to the
temporary file, writes the lines to the temporary file until the delimiter
is reached, closes the temporary file, frees the tokens, frees the minishell
and exits the child process. */
static void	heredoc_child(char *delimiter, char *temp_file,
		t_minishell *minishell)
{
	int	temp_fd;

	change_terminal();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	temp_fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (temp_fd < 0)
	{
		perror("open failed");
		return ;
	}
	while (!write_line(delimiter, temp_fd))
	{
	}
	close(temp_fd);
	free_parsed(minishell->cmd_without_redirects);
	free_minishell(minishell);
	exit(EXIT_SUCCESS);
}

/* heredoc: creates a temporary file and redirects input to it
until a specified delimiter is reached.
It forks the process. In the child process, it changes the terminal
settings, redirects the input to the temporary file, writes the lines
to the temporary file until the delimiter is reached, closes the
temporary file, frees the tokens, frees the minishell and exits the
child process. In the parent process, it waits for the child process
to finish. */
int	heredoc(char *delimiter, t_minishell *minishell)
{
	char	*temp_file;
	pid_t	pid;

	if (delimiter != NULL)
	{
		g_minishell.in_command = 1;
		restore_stdin();
		temp_file = "/tmp/tempfileXXXXXX";
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			return (0);
		}
		if (pid == 0)
			heredoc_child(delimiter, temp_file, minishell);
		else
			waitpid(pid, NULL, 0);
		redirect_input(temp_file);
		unlink(temp_file);
		g_minishell.in_command = 0;
		return (1);
	}
	return (0);
}
