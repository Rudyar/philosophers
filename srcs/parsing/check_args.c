/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:36:42 by arudy             #+#    #+#             */
/*   Updated: 2022/01/31 14:32:31 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	check_digit(int ac, char **av)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (j < ft_strlen(av[i]))
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				ft_error("Only digit & positive args\n");
			j++;
		}
		i++;
	}
}

long long	ft_atoll(char *str)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n);
}

void	check_is_int(int ac, char **av)
{
	int			i;
	long long	res;

	i = 1;
	res = 0;
	while (i < ac)
	{
		if (ft_strlen(av[i]) > 11)
			ft_error("Arg too long\n");
		res = ft_atoll(av[i]);
		if (res > 2147483647 / 1000)
			ft_error("Time too long\n");
		i++;
	}
}

void	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		ft_error("Wrong number of args\n");
	check_digit(ac, av);
	check_is_int(ac, av);
}
