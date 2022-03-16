/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:55:12 by arudy             #+#    #+#             */
/*   Updated: 2022/03/16 17:07:05 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->philo[i].fork_left);
		pthread_mutex_destroy(&data->philo[i].fork_left);
		pthread_mutex_unlock(&data->philo[i].last_eat_mutex);
		pthread_mutex_destroy(&data->philo[i].last_eat_mutex);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
		pthread_join(data->philo[i++].philo, NULL);
	free(data->philo);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

int	main(int ac, char **av)
{
	t_data	data;

	check_args(ac, av);
	init_data(ac, av, &data);
	start_philo(&data);
	clean(&data);
	return (0);
}
