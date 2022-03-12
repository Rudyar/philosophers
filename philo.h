/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:49:46 by arudy             #+#    #+#             */
/*   Updated: 2022/03/12 17:25:38 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	int				count_eat ;
	pthread_t		philo;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
}t_philo;

typedef struct s_data
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_must_eat;
	t_philo	*philo;
}t_data;

size_t	ft_strlen(const char *str);
void	ft_error(char *msg);
void	ft_putstr_fd(char *s, int fd);
void	check_args(int ac, char **av);
void	init_data(int ac, char **av, t_data *data);

#endif
