/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:05:16 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/03 19:16:28 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*check_philosopher_death(void	*data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->pa->die + 1);
	pthread_mutex_lock(&ph->pa->time_eat);
	pthread_mutex_lock(&ph->pa->finish);
	if (!check_end(ph, 0) && !ph->finish && ((actual_time() - ph->ms_eat) \
		>= (long)(ph->pa->die)))
	{
		pthread_mutex_lock(&ph->pa->write_mutex);
		write_status("has died", ph, DEATH_EMOJI);
		pthread_mutex_unlock(&ph->pa->write_mutex);
		check_end(ph, 1);
	}
	pthread_mutex_unlock(&ph->pa->finish);
	pthread_mutex_unlock(&ph->pa->time_eat);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->eat / 10);
	pthread_create(&ph->thread_death_id, NULL, check_philosopher_death, data);
	while (!check_end(ph, 0))
	{
		activity_cycle(ph);
		pthread_mutex_lock(&ph->pa->time_eat);
		pthread_mutex_lock(&ph->pa->finish);
		if ((int)++ph->nb_eat == ph->pa->m_eat)
		{
			ph->finish = 1;
			ph->pa->nb_p_finish++;
			if (ph->pa->nb_p_finish == ph->pa->total)
				check_end(ph, 2);
		}
		pthread_mutex_unlock(&ph->pa->finish);
		pthread_mutex_unlock(&ph->pa->time_eat);
	}
	pthread_join(ph->thread_death_id, NULL);
	return (NULL);
}

int	init_threads(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->a.total)
	{
		p->ph[i].pa = &p->a;
		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
			return (ft_exit("Pthread did not return 0\n"));
	}
	return (1);
}
