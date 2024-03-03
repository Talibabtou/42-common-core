/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:06:00 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/03 19:16:37 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_start_success(t_p *p, int n, int padding)
{
	if (n == 1)
	{
		printf("┌-------┬--------------┬----------------\
-----┬----┐\n");
		printf("| Time  | Philosopher  | Activity      \
      | 🗣️  |\n");
		printf("├-------┼--------------┼----------------\
-----┼----┤\n");
	}
	else if (n == 2)
	{
		printf("├-------┴--------------┴----------------\
-----┼----┤\n");
		printf("| Each Philosopher ate %d time(s)%*s\
| %s |\n", p->a.m_eat, padding, "", SUCCESS_EMOJI);
		printf("└---------------------------------------\
-----┴----┘\n");
	}
}

void	ft_print_failure(void)
{
	printf("├-------┴--------------┴----------------\
-----┼----┤\n");
	printf("| A Philosopher died                    \
     | %s |\n", FAILURE_EMOJI);
	printf("└---------------------------------------\
-----┴----┘\n");
}

int	check_end(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->pa->dead);
	if (i)
		ph->pa->stop = i;
	if (ph->pa->stop)
		return (pthread_mutex_unlock(&ph->pa->dead), 1);
	else
		return (pthread_mutex_unlock(&ph->pa->dead), 0);
}

long int	actual_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (int)(current_time.tv_usec * 0.001);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
