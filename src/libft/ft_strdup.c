/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:47:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/19 12:50:25 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*out;

	len = 0;
	while (str[len])
		len++;
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
