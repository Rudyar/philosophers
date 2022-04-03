/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:05:57 by arudy             #+#    #+#             */
/*   Updated: 2022/04/03 17:31:11 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	sleep_think_routine(t_philo *philo)
{
	print_status("is sleeping\n", philo);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	print_status("is thinking\n", philo);
	if (philo->data->time_to_sleep < philo->data->time_to_eat)
		ft_usleep((philo->data->time_to_eat - philo->data->time_to_sleep) + 1, \
		philo->data);
}

int	eat_routine(t_philo *philo)
{
	lock_fork(philo, 1);
	print_status("has taken a fork\n", philo);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork_left);
		return (1);
	}
	lock_fork(philo, 2);
	print_status("has taken a fork\n", philo);
	pthread_mutex_lock(&philo->last_eat_mutex);
	print_status("is eating\n", philo);
	philo->last_eat = get_time(philo->data) - philo->data->start_time;
	if (philo->data->nb_must_eat != -1)
		philo->count_eat++;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	sleep_think_routine(philo);
	return (0);
}

void	*start_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->philo_id % 2 == 0)
		ft_usleep(p->data->time_to_eat / 10, p->data);
	while (1)
	{
		if (p->data->nb_must_eat != -1 && p->count_eat == p->data->nb_must_eat)
			return (NULL);
		pthread_mutex_lock(&p->data->stop_mutex);
		if (p->data->stop)
		{
			pthread_mutex_unlock(&p->data->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&p->data->stop_mutex);
		if (eat_routine(p))
			return (NULL);
	}
	return (NULL);
}

int	check_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].last_eat_mutex);
			if (data->nb_must_eat != -1 && data->philo[i].count_eat
				== data->nb_must_eat)
			{
				pthread_mutex_unlock(&data->philo[i].last_eat_mutex);
				return (0);
			}
			if (get_time(data) - data->philo[i].last_eat - data->start_time
				> data->time_to_die)
				return (ft_dead(data, i));
			pthread_mutex_unlock(&data->philo[i].last_eat_mutex);
			i++;
		}
	}
	return (0);
}

void	start_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time(data);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].philo, NULL, start_routine,
				&data->philo[i]))
		{
			clean(data);
			ft_error("Can't create thread");
		}
		i++;
	}
	check_death(data);
}
