/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:41:26 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/17 17:04:53 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	point_to_mutex(t_info **data)
{
	t_philo	*ptr;
	long	i;

	i = 0;
	ptr = (*data)->philo;
	while (++i <= (*data)->nb_of_philo)
	{
		ptr->printf = &(*data)->printf;
		ptr->mutex = &(*data)->mutex;
		ptr = ptr->next;
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
