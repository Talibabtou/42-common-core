/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:22:44 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/15 12:31:36 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	nbstr_cmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = i;
	if (s1[i] == '+')
	{
		if (s2[j] != '+')
			i++;
	}
	else
	{
		if (s2[j] == '+')
			j++;
	}
	while (s1[i] != '\0' && s2[j] != '\0' && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

void	ft_strtok(char **av)
{
	static char	*buffer;
	char		*token;
	int			i;

	buffer = av[1];
	if (av[1] && (*buffer != '\0'))
	{
		token = buffer;
		i = 1;
		while (*buffer)
		{
			if (*buffer == ' ')
			{
				*buffer = '\0';
				av[i++] = token;
				token = buffer + 1;
			}
			buffer++;
		}
		if (buffer != token || *buffer != '\0')
			av[i++] = token;
		av[i] = NULL;
	}
	else
		exit(0);
}
