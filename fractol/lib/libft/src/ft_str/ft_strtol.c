/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:40:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/05 10:49:48 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	skip_whitespace(const char **s)
{
	while (**s && ft_isspace((unsigned char)**s))
		++(*s);
}

void	parse_input(const char *nptr, int *sign, const char **endptr)
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

long	convert_and_detect_overflow(const char *nptr, int sign, int base)
{
	long	val;
	int		digit;

	val = 0;
	while (*nptr)
	{
		if (ft_isdigit((unsigned char)*nptr))
			digit = *nptr - '0';
		else if (base == 16 && (*nptr >= 'a' && *nptr <= 'f'))
			digit = *nptr - 'a' + 10;
		else if (base == 16 && (*nptr >= 'A' && *nptr <= 'F'))
			digit = *nptr - 'A' + 10;
		else
			break;
		if (digit >= base)
			break;
		if (val > (LONG_MAX - digit) / base)
			return (sign == 1 ? LONG_MAX : LONG_MIN);
		val = val * base + digit;
		nptr++;
	}
	return (sign * val);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	long	val;
	int		sign;
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
