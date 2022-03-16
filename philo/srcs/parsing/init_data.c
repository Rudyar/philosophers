/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:10:38 by arudy             #+#    #+#             */
/*   Updated: 2022/03/16 17:53:38 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
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
		data->philo[i].is_dead = 0;
		data->philo[i].last_eat = 0;
		pthread_mutex_init(&data->philo[i].fork_left, NULL);
		pthread_mutex_init(&data->philo[i].last_eat_mutex, NULL);
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
