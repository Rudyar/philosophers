/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:00:54 by arudy             #+#    #+#             */
/*   Updated: 2022/04/12 14:32:19 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

long int	get_time(t_data *data)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		clean(data);
		ft_error("Can't get time of the day\n");
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(char *s, t_philo *philo)
{
	long int	elapsed_time;

	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 0)
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		elapsed_time = get_time(philo->data) - philo->data->start_time;
		printf("%ld ", elapsed_time);
		printf("%d %s", philo->philo_id, s);
		pthread_mutex_unlock(&philo->data->write_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

int	ft_dead(t_data *data, int i)
{
	print_status("died\n", &data->philo[i]);
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	pthread_mutex_unlock(&data->philo[i].is_finito_mutex);
	pthread_mutex_unlock(&data->philo[i].last_eat_mutex);
	return (0);
}

void	lock_fork(t_philo *philo, int n)
{
	if (n == 1)
	{
		if (philo->philo_id % 2 == 0)
			pthread_mutex_lock(philo->fork_right);
		else
			pthread_mutex_lock(&philo->fork_left);
	}
	else
	{
		if (philo->philo_id % 2 == 0)
			pthread_mutex_lock(&philo->fork_left);
		else
			pthread_mutex_lock(philo->fork_right);
	}
}

void	ft_usleep(long int time, t_data *data)
{
	long int	start_time;

	start_time = get_time(data);
	while ((get_time(data) - start_time) < time)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		usleep(1000);
	}
}
