/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:08:21 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 19:16:45 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_str(char const *s, char c)
{
	int	n;
	int	check;

	n = 0;
	check = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (check == 0)
				n++;
			check = 1;
		}
		else
			check = 0;
		s++;
	}
	return (n);
}

static char	*ft_create_sub_string(char const *s, char c, int *j)
{
	char	*res;
	int		k;

	k = 0;
	while (s[*j] == c)
		(*j)++;
	while (s[*j + k] != c && s[*j + k])
		k++;
	res = ft_substr(s, *j, k);
	*j += k;
	return (res);
}

static void	free_split(char **strs, int count)
{
	int	i;

	for (i = 0; i < count; i++)
	{
		if (strs[i])
			free(strs[i]);
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		n;
	int		i;
	int		j;

	n = ft_count_str(s, c);
	dest = (char **)ft_gc(malloc((n + 1) * sizeof(char *)));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		dest[i] = ft_gc(ft_create_sub_string(s, c, &j));
		if (!dest[i])
		{
			free_split(dest, i);
			return (NULL);
		}
		i++;
	}
	dest[n] = 0;
	return (dest);
}
