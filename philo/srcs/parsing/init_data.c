/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:10:38 by arudy             #+#    #+#             */
/*   Updated: 2022/03/17 19:45:20 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	mutex_error(int i, int n, t_data *data)
{
	int	j;

	j = 0;
	while (j < i)
		pthread_mutex_destroy(&data->philo[j++].fork_left);
	if (n == 2)
	{
		j = 0;
		while (j < i)
			pthread_mutex_destroy(&data->philo[j++].last_eat_mutex);
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->philo);
	ft_error("Can't init forks mutexs ");
}

void	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->write_mutex, NULL))
	{
		free(data->philo);
		ft_error("Can't init write mutex\n");
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL))
	{
		pthread_mutex_destroy(&data->write_mutex);
		free(data->philo);
		ft_error("Can't init stop mutex\n");
	}
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].fork_right = NULL;
		data->philo[i].count_eat = 0;
		data->philo[i].data = data;
		data->philo[i].last_eat = 0;
		if (pthread_mutex_init(&data->philo[i].fork_left, NULL))
			return (mutex_error(i, 1, data));
		if (pthread_mutex_init(&data->philo[i].last_eat_mutex, NULL))
			return (mutex_error(i, 2, data));
		i++;
	}
	i = 0;
	while (i < data->nb_philo - 1)
	{
		data->philo[i].fork_right = &data->philo[i + 1].fork_left;
		i++;
	}
	data->philo[i].fork_right = &data->philo[0].fork_left;
}

void	init_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->stop = 0;
	if (ac == 6 && ft_atoi(av[5]) == 0)
		ft_error("Only > 0 args\n");
	else if (ac == 6 && ft_atoi(av[5]) > 0)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	if (data->nb_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		ft_error("Only > 0 args\n");
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		ft_error("Malloc problem\n");
	init_philo(data);
	init_mutex(data);
}
