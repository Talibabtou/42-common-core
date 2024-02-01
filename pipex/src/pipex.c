/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:07:24 by gdumas            #+#    #+#             */
/*   Updated: 2024/02/01 09:50:44 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env, int fd)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (s_cmd == NULL)
		exit (-1);
	path = get_path(s_cmd[0], env);
	if (!path)
		exit_handler(3, NULL, s_cmd, fd);
	else if (execve(path, s_cmd, env) == -1)
		exit_handler(4, NULL, s_cmd, fd);
}

pid_t	first_cmd(char **av, int *p_fd, char **env)
{
	int		fd;
	pid_t	pid;

	fd = open_file(av[1], 0);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
	{
		dup2(fd, 0);
		close (fd);
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(av[2], env, fd);
	}
	else if (pid > 0)
	{
		close(fd);
		close(p_fd[1]);
	}
	return (pid);
}

pid_t	second_cmd(char **av, int *p_fd, char **env)
{
	int		fd;
	pid_t	pid;

	fd = open_file(av[4], 1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
	{
		dup2(fd, 1);
		close(fd);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		close(p_fd[1]);
		exec(av[3], env, fd);
	}
	if (pid > 0)
	{
		close(fd);
		close(p_fd[0]);
	}
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid[2];
	int		status[2];
	int		last_error;

	if (ac != 5)
		exit_handler(1, NULL, NULL, 0);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid[0] = first_cmd(av, p_fd, env);
	pid[1] = second_cmd(av, p_fd, env);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	last_error = 0;
	if (WIFEXITED(status[0]))
		last_error = WEXITSTATUS(status[0]);
	if (WIFEXITED(status[1]))
		last_error = WEXITSTATUS(status[1]);
	return (close (p_fd[0]), close (p_fd[1]), last_error);
}
