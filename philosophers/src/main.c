/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:04:46 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/03 19:03:44 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *error)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(error, 2);
	return (0);
}

static int	check_program_termination(t_p *p)
{
	int	stop;

	stop = 0;
	if (p->a.stop)
		return (1);
	pthread_mutex_lock(&p->a.dead);
	stop = p->a.stop;
	pthread_mutex_unlock(&p->a.dead);
	return (stop);
}

static void	choose_print(t_p *p)
{
	int	max_width;
	int	padding;

	padding = 0;
	max_width = 13;
	if (p->a.stop == 1)
		ft_print_failure();
	else if (p->a.stop == 2)
	{
		padding = max_width - ft_intlen(p->a.m_eat);
		ft_print_start_success(p, 2, padding);
	}
}

static void	stop_philos(t_p *p)
{
	int	i;

	while (!check_program_termination(p))
		ft_usleep(p->a.die / 2);
	i = -1;
	while (++i < p->a.total)
	{
		pthread_join(p->ph[i].thread_id, NULL);
		if (pthread_mutex_destroy(&p->ph[i].l_f) != 0)
			ft_exit("Mutex destroy failed\n");
	}
	if (pthread_mutex_destroy(&p->a.dead) != 0)
		ft_exit("Mutex destroy failed\n");
	pthread_mutex_lock(&p->a.write_mutex);
	choose_print(p);
	pthread_mutex_unlock(&p->a.write_mutex);
	if (pthread_mutex_destroy(&p->a.write_mutex) != 0)
		ft_exit("Mutex destroy failed\n");
}

int	main(int argc, char **argv)
{
	t_p	p;

	if (!(parse_args(argc, argv, &p)))
		return (ft_exit("Invalid arguments\n"));
	p.ph = malloc(sizeof(t_philo) * p.a.total);
	if (!p.ph)
		return (ft_exit("Structure malloc failed\n"));
	ft_print_start_success(&p, 1, 0);
	if (!initialize(&p) || !init_threads(&p))
	{
		free(p.ph);
		return (ft_exit("Initialization or thread creation failed\n"), 0);
	}
	stop_philos(&p);
	free(p.ph);
	return (0);
}
