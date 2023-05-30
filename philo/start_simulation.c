/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:41:22 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/17 18:44:38 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_destroy_forks(t_info **data, long len, long i, long choose)
{
	t_philo	*ptr;

	len = (*data)->nb_of_philo;
	ptr = (*data)->philo;
	if (!choose)
	{
		pthread_mutex_init(&(*data)->mutex, NULL);
		pthread_mutex_init(&(*data)->printf, NULL);
		while (++i <= len)
		{
			pthread_mutex_init(&ptr->fork, NULL);
			ptr = ptr->next;
		}
	}
	else
	{
		pthread_mutex_destroy(&(*data)->mutex);
		pthread_mutex_destroy(&(*data)->printf);
		while (++i <= len)
		{
			pthread_mutex_destroy(&ptr->fork);
			ptr = ptr->next;
		}
	}
}

/*----------------------------------------------------------------*/

static void	philo_actions(t_philo **ptr)
{
	(pthread_mutex_lock(&(*ptr)->fork), pthread_mutex_lock((*ptr)->printf));
	printf("%lu	%lu has taken a fork\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	pthread_mutex_unlock((*ptr)->printf);
	pthread_mutex_lock(&(*ptr)->next->fork);
	pthread_mutex_lock((*ptr)->printf);
	printf("%lu	%lu has taken a fork\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	pthread_mutex_unlock((*ptr)->printf);
	(pthread_mutex_lock((*ptr)->mutex), pthread_mutex_lock((*ptr)->printf));
	printf("%lu	%lu is eating\n", get_cur_time(&(*ptr), 1), (*ptr)->nb);
	pthread_mutex_unlock((*ptr)->printf);
	if ((*ptr)->nb_must_eat != -1)
		(*ptr)->nb_times_eat++;
	pthread_mutex_unlock((*ptr)->mutex);
	my_usleep((*ptr)->time_to_eat, &(*ptr));
	pthread_mutex_unlock(&(*ptr)->fork);
	pthread_mutex_unlock(&(*ptr)->next->fork);
	pthread_mutex_lock((*ptr)->printf);
	printf("%lu	%lu is sleeping\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	pthread_mutex_unlock((*ptr)->printf);
	my_usleep((*ptr)->time_to_sleep, &(*ptr));
	pthread_mutex_lock((*ptr)->printf);
	printf("%lu	%lu is thinking\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	pthread_mutex_unlock((*ptr)->printf);
}

/*----------------------------------------------------------------*/

static void	*routine(void *arg)
{
	t_philo	*ptr;

	ptr = (t_philo *)arg;
	if (ptr->nb % 2 == 0)
		usleep(400);
	while (1)
		philo_actions(&ptr);
	return (NULL);
}

/*----------------------------------------------------------------*/

void	start_simulation(t_info *data, char **av)
{
	t_philo	*ptr;
	long	i;

	create_list(&data, av);
	init_destroy_forks(&data, data->nb_of_philo, 0, 0);
	point_to_mutex(&data);
	ptr = data->philo;
	i = 0;
	while (data->philo && ++i <= data->nb_of_philo)
	{
		if (pthread_create(&ptr->philo, NULL, routine, ptr))
		{
			printf("Error: Create thread\n");
			break ;
		}
		ptr = ptr->next;
	}
	check_death(&data);
	init_destroy_forks(&data, data->nb_of_philo, 0, 1);
}
