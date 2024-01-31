/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:10:26 by gdumas            #+#    #+#             */
/*   Updated: 2023/11/28 16:10:58 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptrlen(size_t ptr)
{
	int	i;

	i = 0;
	while (ptr != 0)
	{
		i++;
		ptr = ptr / 16;
	}
	return (i);
}

void	ft_putptr(size_t ptr)
{
	if (ptr >= 16)
	{
		ft_putptr(ptr / 16);
		ft_putptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + '0'), 1);
		else
			ft_putchar_fd((ptr - 10 + 'a'), 1);
	}
}

int	ft_printptr(unsigned long long ptr)
{
	int	nprinted;

	nprinted = 0;
	if (ptr == 0)
		nprinted += write(1, "(nil)", 5);
	else
	{
		nprinted += write(1, "0x", 2);
		ft_putptr(ptr);
		nprinted += ft_ptrlen(ptr);
	}
	return (nprinted);
}
