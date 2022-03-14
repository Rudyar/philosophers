/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:05:57 by arudy             #+#    #+#             */
/*   Updated: 2022/03/14 19:02:07 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

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
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	ft_usleep(philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	*start_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->philo_id % 2 == 0)
		ft_usleep(p->data->time_to_eat / 10);
	while (1)
		eat_routine(p);
	return (NULL);
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
}
