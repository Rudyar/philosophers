/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:55:12 by arudy             #+#    #+#             */
/*   Updated: 2022/03/14 18:43:49 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->philo[i++].fork_left);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	check_args(ac, av);
	init_data(ac, av, &data);
	start_philo(&data);
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].philo, NULL);
		i++;
	}
	destroy_mutex(&data);
	free(data.philo);
	return (0);
}
