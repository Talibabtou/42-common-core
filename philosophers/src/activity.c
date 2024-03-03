/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:03:13 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/03 19:16:09 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(char *str, t_philo *ph, char *emoji)
{
	long int	time;
	int			max_width;
	int			padding;

	max_width = 20;
	time = -1;
	time = actual_time() - ph->pa->start_t;
	if (time >= 0 && time <= INT_MAX && !check_end(ph, 0))
	{
		printf("| %-6ld| ", time);
		printf("Philo n°%-5d|", ph->id);
		padding = max_width - ft_strlen(str);
		printf(" %s%*s|", str, padding, "");
		printf(" %s |\n", emoji);
	}
}

void	sleep_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is sleeping", ph, SLEEPING_EMOJI);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->sleep);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is thinking", ph, THINKING_EMOJI);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

void	activity_cycle(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("has taken a fork", ph, FORK_EMOJI);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	if (!ph->r_f)
	{
		pthread_mutex_unlock(&ph->l_f);
		ft_usleep(ph->pa->die * 2);
		return ;
	}
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("has taken a fork", ph, FORK_EMOJI);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	pthread_mutex_lock(&ph->pa->time_eat);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&ph->pa->time_eat);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is eating", ph, EATING_EMOJI);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	pthread_mutex_unlock(ph->r_f);
	pthread_mutex_unlock(&ph->l_f);
	ft_usleep(ph->pa->eat);
	sleep_think(ph);
}
