/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:07:30 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/31 16:39:51 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

int		open_file(char *file, int n);
char	*get_env(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	ft_free_tab(char **tab);
void	exit_handler(int n_exit, char *file, char **s_cmd, int fd);

void	exec(char *cmd, char **env, int fd);
int		first_cmd(char **av, int *p_fd, char **env);
int		second_cmd(char **av, int *p_fd, char **env);
int		main(int ac, char **av, char **env);

void	ft_putendl_fd(char *str, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *str);
char	*ft_strchr(char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);

#endif