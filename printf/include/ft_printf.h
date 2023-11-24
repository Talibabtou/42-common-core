/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:58:24 by gdumas            #+#    #+#             */
/*   Updated: 2023/11/24 15:42:43 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_formats(va_list	args, const char format);
int		ft_printchar(int c);
void	ft_putstr(char *str);
int		ft_printstr(char *str);
int		ft_printpercent(void);
int		ft_printnbr(int n);
int		ft_numlen(unsigned int num);
char	*ft_uitoa(unsigned int n);
int		ft_printunsigned(unsigned int n);
int		ft_ptrlen(size_t ptr);
void	ft_putptr(size_t ptr);
int		ft_printptr(unsigned long long ptr);
int		ft_hexlen(unsigned	int num);
void	ft_puthex(unsigned int num, const char format);
int		ft_printhex(unsigned int num, const char format);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);

#endif