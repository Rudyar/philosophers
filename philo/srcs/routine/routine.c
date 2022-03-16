/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:05:57 by arudy             #+#    #+#             */
/*   Updated: 2022/03/16 18:20:25 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	sleep_think_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	ft_usleep(philo->data->time_to_sleep, philo->data);
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
	philo->last_eat = get_time(philo->data) - philo->data->start_time;
	if (philo->data->nb_must_eat != -1)
		philo->count_eat++;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	*start_routine(void *philo)
{
	t_philo	*p;
	int		dead;

	p = (t_philo *)philo;
	pthread_mutex_lock(&p->data->stop_mutex);
	dead = p->data->stop;
	pthread_mutex_unlock(&p->data->stop_mutex);
	if (p->philo_id % 2 == 0)
		ft_usleep(p->data->time_to_eat / 10, p->data);
	while (dead == 0)
	{
		eat_routine(p);
		sleep_think_routine(p);
		pthread_mutex_lock(&p->data->stop_mutex);
		dead = p->data->stop;
		pthread_mutex_unlock(&p->data->stop_mutex);
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
			if (get_time(data) - data->philo[i].last_eat - data->start_time
				> data->time_to_die)
				return (ft_dead(data, i));
			pthread_mutex_unlock(&data->philo[i].last_eat_mutex);
			i++;
		}
		if (data->nb_must_eat != -1)
		{
			i = 0;
			while (i < data->nb_philo
				&& data->philo[i].count_eat == data->nb_must_eat)
				i++;
			if (i == data->nb_philo)
				return (1);
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
			free(data->philo);
			ft_error("Can't create thread");
		}
		i++;
	}
	while (1)
	{
		if (check_death(data) == 1)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return ;
		}
	}
}
