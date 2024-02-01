/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:47:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/31 16:45:27 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	length;

	length = ft_strlen(str);
	result = (char *)malloc((length + 1) * sizeof(char));
	if (!result)
		return (NULL);
	length = 0;
	while (str[length] != '\0')
	{
		result[length] = str[length];
		length++;
	}
	result[length] = '\0';
	return (result);
}
