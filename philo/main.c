/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:41:46 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/22 18:01:31 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*----------------------------------------------------------------*/

static int	check_args(char **str, int len)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (!j && str[i][j] == '+')
				j++;
			if (!ft_isdigit(str[i][j]))
				return (write(2, "Invalid arguments\n", 18), 0);
		}
	}
	i = -1;
	while (++i < len - 1)
	{
		if (!ft_atoi(str[i]))
			return (write(2, "Invalide number: 0\n", 19), 0);
	}
	return (1);
}

/*----------------------------------------------------------------*/

int	main(int ac, char **av)
{
	t_info	data;

	if (ac == 5 || ac == 6)
	{
		if (check_args(av + 1, ac))
		{
			start_simulation(&data, av);
			ft_lstclear(&data.philo, data.nb_of_philo);
		}
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
