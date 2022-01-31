/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:55:12 by arudy             #+#    #+#             */
/*   Updated: 2022/01/31 14:39:45 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	check_args(ac, av);
	init_data(ac, av, &data);
	// printf("%d\n", data.nb_philo);
	// printf("%d\n", data.time_to_die);
	// printf("%d\n", data.time_to_eat);
	// printf("%d\n", data.time_to_sleep);
	// printf("%d\n", data.nb_must_eat);
	return (0);
}
