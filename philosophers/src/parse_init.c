/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:04:21 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/03 18:32:04 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
	{
		sum = (sum * 10) + (str[i] - '0');
		if (sum > INT_MAX)
			return (-1);
	}
	return (sum);
}

static int	numeric(char **argv)
{
	int	j;
	int	i;

	j = 1;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_p *p)
{
	if ((argc == 5 || argc == 6) && numeric(argv))
	{
		p->a.total = ft_atoi(argv[1]);
		p->a.die = ft_atoi(argv[2]);
		p->a.eat = ft_atoi(argv[3]);
		p->a.sleep = ft_atoi(argv[4]);
		p->a.m_eat = -1;
		if (argc == 6)
			p->a.m_eat = ft_atoi(argv[5]);
		if (p->a.total <= 0 || p->a.die <= 0 || p->a.eat <= 0 \
			|| p->a.sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}

static void	init_mutex(t_p *p)
{
	if (pthread_mutex_init(&p->a.write_mutex, NULL) != 0)
		ft_exit("Mutex initialization failed\n");
	if (pthread_mutex_init(&p->a.dead, NULL) != 0)
		ft_exit("Mutex initialization failed\n");
	if (pthread_mutex_init(&p->a.time_eat, NULL) != 0)
		ft_exit("Mutex initialization failed\n");
	if (pthread_mutex_init(&p->a.finish, NULL) != 0)
		ft_exit("Mutex initialization failed\n");
}

int	initialize(t_p *p)
{
	int	i;

	i = 0;
	p->a.start_t = actual_time();
	p->a.stop = 0;
	p->a.nb_p_finish = 0;
	init_mutex(p);
	while (i < p->a.total)
	{
		p->ph[i].id = i + 1;
		p->ph[i].ms_eat = p->a.start_t;
		p->ph[i].nb_eat = 0;
		p->ph[i].finish = 0;
		p->ph[i].r_f = NULL;
		if (pthread_mutex_init(&p->ph[i].l_f, NULL) != 0)
			ft_exit("Mutex initialization failed\n");
		if (p->a.total == 1)
			return (1);
		if (i == p->a.total - 1)
			p->ph[i].r_f = &p->ph[i - 1].l_f;
		else
			p->ph[i].r_f = &p->ph[i + 1].l_f;
		i++;
	}
	return (1);
}
