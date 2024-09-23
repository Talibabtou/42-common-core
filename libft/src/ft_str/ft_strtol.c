/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:40:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/16 12:58:37 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_whitespace(const char **s)
{
	while (**s && ft_isspace((unsigned char)**s))
		++(*s);
}

static void	parse_input(const char *nptr, int *sign, const char **endptr)
{
	if (!nptr)
	{
		*sign = 0;
		*endptr = NULL;
		return ;
	}
	skip_whitespace(&nptr);
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			*sign = -1;
		else
			*sign = 1;
	}
	*endptr = nptr;
}

static int	convert_digit(char c, int base)
{
	if (ft_isdigit((unsigned char)c))
		return (c - '0');
	if (base == 16)
	{
		if (c >= 'a' && c <= 'f')
			return (c - 'a' + 10);
		if (c >= 'A' && c <= 'F')
			return (c - 'A' + 10);
	}
	return (-1);
}

static long	convert_and_detect_overflow(const char *nptr, int sign, int base)
{
	long	val;
	int		digit;

	val = 0;
	while (*nptr)
	{
		digit = convert_digit(*nptr, base);
		if (digit == -1 || digit >= base)
			break ;
		if (val > (LONG_MAX - digit) / base)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		val = val * base + digit;
		nptr++;
	}
	return (sign * val);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	long		val;
	int			sign;
	const char	*end;

	sign = 1;
	parse_input(nptr, &sign, &end);
	val = convert_and_detect_overflow(end, sign, base);
	if (endptr)
	{
		while (*end && ft_isdigit((unsigned char)*end))
			end++;
		*endptr = (char *)end;
	}
	return (val);
}
