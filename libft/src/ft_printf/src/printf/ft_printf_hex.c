/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:36:03 by gdumas            #+#    #+#             */
/*   Updated: 2023/11/24 15:44:17 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlen(unsigned	int num)
{
	int	i;

	i = 0;
	while (num != 0)
	{
		i++;
		num = num / 16;
	}
	return (i);
}

void	ft_puthex(unsigned int num, const char format)
{
	if (num >= 16)
	{
		ft_puthex(num / 16, format);
		ft_puthex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	ft_printhex(unsigned int num, const char format)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_puthex(num, format);
	return (ft_hexlen(num));
}
