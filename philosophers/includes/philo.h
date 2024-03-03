/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:18:07 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/03 19:16:03 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* includes */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/* emojis */

# define FORK_EMOJI "🍴"
# define EATING_EMOJI "🍲"
# define SLEEPING_EMOJI "😴"
# define THINKING_EMOJI "🧠"
# define DEATH_EMOJI "💀"
# define SUCCESS_EMOJI "✅"
# define FAILURE_EMOJI "❌"

/* structures */

typedef struct s_arg
{
	int				total;
	int				die;
	int				eat;
	int				sleep;	
	int				m_eat;
	long int		start_t;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead;
	pthread_mutex_t	time_eat;
	pthread_mutex_t	finish;
	int				nb_p_finish;
	int				stop;
}	t_arg;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_t		thread_death_id;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	l_f;
	t_arg			*pa;
	long int		ms_eat;
	unsigned int	nb_eat;
	int				finish;
}	t_philo;

typedef struct s_p
{
	t_philo			*ph;
	t_arg			a;
}	t_p;

/* functions */

int			parse_args(int argc, char **argv, t_p *p);
int			initialize(t_p *p);
int			ft_exit(char *str);
void		write_status(char *str, t_philo *ph, char *emoji);
long int	actual_time(void);
void		ft_putstr_fd(char *s, int fd);
void		ft_usleep(long int time_in_ms);
int			init_threads(t_p *p);
void		activity_cycle(t_philo *ph);
int			check_end(t_philo *ph, int i);
int			ft_strlen(char *str);
int			ft_intlen(int n);
void		ft_print_start_success(t_p *p, int n, int padding);
void		ft_print_failure(void);

#endif