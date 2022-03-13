/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:05:57 by arudy             #+#    #+#             */
/*   Updated: 2022/03/13 16:58:06 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	
	printf("philo id : %d\n\n", p->philo_id);
	return (NULL);
}

void	start_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo[i].philo_id % 2 == 0)
			usleep(1000);
		pthread_create(&data->philo[i].philo, NULL, routine, &data->philo[i]);
		i++;
	}
}
