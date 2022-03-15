/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:05:57 by arudy             #+#    #+#             */
/*   Updated: 2022/03/15 16:49:23 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	sleep_think_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	ft_usleep(philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_left);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("is eating\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	if (philo->data->nb_must_eat != -1)
		philo->count_eat++;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	*start_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->philo_id % 2 == 0)
		ft_usleep(p->data->time_to_eat / 10);
	while (p->data->stop == 0)
	{
		eat_routine(p);
		// if (p->count_eat == p->data->nb_must_eat)
		// 	break ;
		sleep_think_routine(p);
	}
	return (NULL);
}

int	check_death(t_data *data)
{
	int	i;
	int	j;

	while (j != data->nb_must_eat)
	{
		i = 0;
		j = 0;
		while (i < data->nb_philo)
		{
			if (get_time() - data->philo[i].last_eat - data->start_time > data->time_to_die)
			{
			pthread_mutex_lock(&data->write_mutex);
			pthread_mutex_lock(&data->stop_mutex);
			print_status("died\n", &data->philo[i]);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (1);
			pthread_mutex_unlock(&data->write_mutex);
			}
			i++;
		}
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->philo[i].count_eat == data->nb_must_eat)
				j++;
			i++;
		}
		if (j == data->nb_must_eat)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (1);
		}
	}
	return (0);
}

void	start_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].philo, NULL, start_routine,
			&data->philo[i]);
		i++;
	}
	while (1)
	{
		if (check_death(data) == 1)
		{
			break ;
		}
	}
}
