/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:41:26 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/22 18:08:32 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_wait(int *tab, long nb_philo)
{
	long	check;
	int		st;
	long	i;

	check = 0;
	while (check != nb_philo)
	{
		if (waitpid(-1, &st, 0) != -1)
		{
			if (WIFEXITED(st))
			{
				if (WEXITSTATUS(st) == 1)
					check++;
				else
				{
					i = -1;
					while (++i < nb_philo)
						kill(tab[i], SIGTERM);
					break ;
				}
			}
		}
		else
			write(2, "Error: waitpid\n", 15);
	}
}

/*----------------------------------------------------------------*/

long	ft_atoi(const char *str)
{
	long	res;
	long	last;

	res = 0;
	if (*str == 43)
		str++;
	while (*str != '\0' && *str >= 48 && *str <= 57)
	{
		last = res;
		res = res * 10 + *str - 48;
		str++;
	}
	return (res);
}

/*----------------------------------------------------------------*/

long	get_cur_time(t_philo **lst, int if_eating)
{
	struct timeval	cur_time;
	long			time_in_ms;

	gettimeofday(&cur_time, NULL);
	time_in_ms = (cur_time.tv_sec - (*lst)->first_start.tv_sec) * 1000
		+ (cur_time.tv_usec - (*lst)->first_start.tv_usec) / 1000;
	if (if_eating)
		(*lst)->last_time_eat = time_in_ms;
	return (time_in_ms);
}

/*----------------------------------------------------------------*/

void	my_usleep(long miliseconds, t_philo **lst)
{
	struct timeval	cur_time;

	gettimeofday(&(*lst)->start_time, NULL);
	(*lst)->time_passed = 0;
	while ((*lst)->time_passed < miliseconds)
	{
		usleep(100);
		gettimeofday(&cur_time, NULL);
		(*lst)->time_passed = (cur_time.tv_sec - (*lst)->start_time.tv_sec)
			* 1000 + (cur_time.tv_usec - (*lst)->start_time.tv_usec) / 1000;
	}
}

/*----------------------------------------------------------------*/

int	r_u_dead(t_philo *lst)
{
	struct timeval	cur_time;
	long			som_now;

	gettimeofday(&cur_time, NULL);
	som_now = (cur_time.tv_sec - lst->first_start.tv_sec) * 1000
		+ (cur_time.tv_usec - lst->first_start.tv_usec) / 1000;
	if (som_now - lst->last_time_eat >= lst->time_to_die)
		return (1);
	return (0);
}
