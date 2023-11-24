/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:21:11 by gdumas            #+#    #+#             */
/*   Updated: 2023/11/24 15:44:21 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_printnbr(int n)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_itoa(n);
	i = ft_printstr(num);
	free(num);
	return (i);
}

int	ft_numlen(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_numlen(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

int	ft_printunsigned(unsigned int n)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_uitoa(n);
	i = ft_printstr(num);
	free(num);
	return (i);
}
