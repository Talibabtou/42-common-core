/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:07:27 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/29 15:38:15 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	exit_handler(int n_exit, char *file, char **s_cmd, int fd)
{
	if (n_exit == 1)
		ft_putstr_fd("correct format:\"./pipex infile cmd cmd outfile\"\n", 2);
	else if (n_exit == 2)
	{
		ft_putstr_fd("pipex: No such file or directory: ", 2);
		ft_putendl_fd(file, 2);
	}
	else if (n_exit == 3)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		close(fd);
		exit (127);
	}
	else if (n_exit == 4)
	{
		ft_putstr_fd("pipex: Permission denied: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		close(fd);
		exit (126);
	}
	exit(EXIT_FAILURE);
}

int	open_file(char *file, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
		fd = open(file, O_RDONLY, 0644);
	if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (in_or_out == 0)
			fd = open("/dev/null", O_RDONLY, 0644);
		else
			fd = open("/dev/null", O_WRONLY, 0644);
		exit_handler(2, file, NULL, fd);
	}
	return (fd);
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		if (sub)
			free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	if (!cmd || !cmd[0])
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	allpath = ft_split(get_env("PATH", env), ':');
	if (!allpath)
		return (NULL);
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i] && s_cmd)
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free (path_part);
		if (exec && access(exec, F_OK) == 0)
			return (ft_free_tab(s_cmd), exec);
		free(exec);
	}
	return (ft_free_tab(allpath), ft_free_tab(s_cmd), NULL);
}
