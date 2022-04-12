/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:49:46 by arudy             #+#    #+#             */
/*   Updated: 2022/04/12 14:18:00 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
typedef struct timeval	t_timeval;

struct	s_philo
{
	int				philo_id;
	int				count_eat;
	long int		last_eat;
	int				is_finito;
	pthread_t		philo;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	is_finito_mutex;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	t_data			*data;
};

struct	s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				stop;
	long int		start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	stop_mutex;
	t_philo			*philo;
};

size_t		ft_strlen(const char *str);
long int	get_time(t_data *data);
int			ft_atoi(const char *str);
int			ft_dead(t_data *data, int i);
void		ft_error(char *msg);
void		check_args(int ac, char **av);
void		init_data(int ac, char **av, t_data *data);
void		start_philo(t_data *data);
void		lock_fork(t_philo *philo, int n);
void		ft_usleep(long int time, t_data *data);
void		print_status(char *s, t_philo *philo);
void		clean(t_data *data);

#endif
