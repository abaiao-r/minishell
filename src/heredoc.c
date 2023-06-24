/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:42:49 by quackson          #+#    #+#             */
/*   Updated: 2023/06/23 23:49:27 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	write_line(char *delimiter, int temp_fd)
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

/**
 * The function changes the terminal settings to disable the VQUIT character.
 */
void	change_terminal(void)
{
	struct termios	term_settings;

	tcgetattr(STDIN_FILENO, &term_settings);
	term_settings.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

void	heredoc_child(char *delimiter, char *temp_file, t_minishell *minishell)
{
	int		temp_fd;

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

/**
 * This function creates a temporary file and redirects input to it
 * until a specified delimiter is reached.
 * 
 * @param delimiter The delimiter is a string that marks the end of
 * the input for the heredoc command. The user will input lines of
 * text until they enter the delimiter string, at which point the input
 * will be saved to a temporary file.
 * @param minishell The parameter `minishell` is a pointer to a
 * `t_minishell` struct, which likely contains information about the
 * current state of the minishell program.
 * @return The function does not have a return value, so nothing is
 * being returned.
 */
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
