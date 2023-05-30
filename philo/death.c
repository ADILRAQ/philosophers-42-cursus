/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:46:07 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/17 17:16:44 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	detach_threads(t_philo **lst, long nb)
{
	t_philo	*ptr;
	long	i;

	ptr = *lst;
	i = 0;
	while (++i <= nb)
	{
		if (pthread_detach(ptr->philo))
			printf("Error: Detach thread\n");
		ptr = ptr->next;
	}
}

/*----------------------------------------------------------------*/

static int	all_threads_ate(t_info **data)
{
	t_philo	*ptr;
	long	i;

	ptr = (*data)->philo;
	i = 0;
	while (++i <= (*data)->nb_of_philo)
	{
		if (ptr->nb_times_eat < (*data)->nb_must_eat)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

/*----------------------------------------------------------------*/

static int	r_u_dead(t_philo *lst)
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

/*----------------------------------------------------------------*/

void	check_death(t_info **data)
{
	t_philo	*ptr;

	ptr = (*data)->philo;
	while (1)
	{
		pthread_mutex_lock(&(*data)->mutex);
		if ((*data)->nb_must_eat != -1 && all_threads_ate(data))
			break ;
		if (r_u_dead(ptr))
		{
			pthread_mutex_lock(&(*data)->printf);
			detach_threads(&(*data)->philo, (*data)->nb_of_philo);
			printf("\033[0;31m%lu	%lu died\n", get_cur_time(&ptr, 0), ptr->nb);
			break ;
		}
		pthread_mutex_unlock(&(*data)->mutex);
		ptr = ptr->next;
	}
}
