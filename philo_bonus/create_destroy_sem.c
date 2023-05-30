/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy_sem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:00:39 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/22 14:28:57 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create__sem(t_info **data, long nb)
{
	t_philo	*ptr;
	long	i;

	(*data)->sem = sem_open("sem", O_CREAT, 0600, nb);
	(*data)->printf = sem_open("printf", O_CREAT, 0600, 1);
	if ((*data)->sem == SEM_FAILED || (*data)->printf == SEM_FAILED)
	{
		write(2, "Error: sem_open\n", 16);
		return (0);
	}
	i = -1;
	ptr = (*data)->philo;
	while (++i < nb)
	{
		ptr->eat = sem_open(ptr->str, O_CREAT, 0600, 1);
		if (ptr->eat == SEM_FAILED)
		{
			write(2, "Error: sem_open\n", 16);
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

/*----------------------------------------------------------------*/

void	destroy__sem(t_info **data, int choose)
{
	t_philo	*ptr;
	long	i;

	if (choose)
	{
		sem_close((*data)->sem);
		sem_close((*data)->printf);
		i = -1;
		ptr = (*data)->philo;
		while (++i < (*data)->nb_of_philo)
		{
			sem_close(ptr->eat);
			ptr = ptr->next;
		}
	}
	sem_unlink("sem");
	sem_unlink("printf");
	i = -1;
	ptr = (*data)->philo;
	while (++i < (*data)->nb_of_philo)
	{
		sem_unlink(ptr->str);
		ptr = ptr->next;
	}
}

/*----------------------------------------------------------------*/

void	init_time_sem(t_info **data, long nb)
{
	struct timeval	start_time;
	t_philo			*ptr;
	long			i;

	if (!(*data)->philo)
		return ;
	gettimeofday(&start_time, NULL);
	ptr = (*data)->philo;
	i = -1;
	while (++i < nb)
	{
		ptr->first_start = start_time;
		ptr->fork = (*data)->sem;
		ptr->printf = (*data)->printf;
		ptr = ptr->next;
	}
}
