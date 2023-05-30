/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:06:52 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/22 17:27:47 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_actions(t_philo **ptr)
{
	if ((*ptr)->nb_must_eat != -1
		&& (*ptr)->nb_times_eat == (*ptr)->nb_must_eat)
		exit(1);
	(sem_wait((*ptr)->fork), sem_wait((*ptr)->printf));
	printf("%lu	%lu has taken a fork\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	(sem_post((*ptr)->printf), sem_wait((*ptr)->fork));
	sem_wait((*ptr)->printf);
	printf("%lu	%lu has taken a fork\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	(sem_post((*ptr)->printf), sem_wait((*ptr)->printf), sem_wait((*ptr)->eat));
	printf("%lu	%lu is eating\n", get_cur_time(&(*ptr), 1), (*ptr)->nb);
	(sem_post((*ptr)->eat), sem_post((*ptr)->printf));
	if ((*ptr)->nb_must_eat != -1)
		(*ptr)->nb_times_eat++;
	my_usleep((*ptr)->time_to_eat, &(*ptr));
	(sem_post((*ptr)->fork), sem_post((*ptr)->fork));
	sem_wait((*ptr)->printf);
	printf("%lu	%lu is sleeping\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	sem_post((*ptr)->printf);
	my_usleep((*ptr)->time_to_sleep, &(*ptr));
	sem_wait((*ptr)->printf);
	printf("%lu	%lu is thinking\n", get_cur_time(&(*ptr), 0), (*ptr)->nb);
	sem_post((*ptr)->printf);
}

/*----------------------------------------------------------------*/

static void	*routine(void *arg)
{
	t_philo	*ptr;

	ptr = (t_philo *)arg;
	while (1)
		philo_actions(&ptr);
	return (NULL);
}

/*----------------------------------------------------------------*/

static void	start_child(t_philo **lst)
{
	pthread_t	th;

	if (pthread_create(&th, NULL, routine, *lst))
	{
		write(2, "Error: Create a thread\n", 23);
		exit(0);
	}
	while (1)
	{
		sem_wait((*lst)->eat);
		if (r_u_dead((*lst)))
		{
			sem_wait((*lst)->printf);
			printf("\033[0;31m%lu	%lu died\n",
				get_cur_time(&(*lst), 0), (*lst)->nb);
			exit(2);
		}
		sem_post((*lst)->eat);
	}
}

/*----------------------------------------------------------------*/

static void	create_childs(t_info *data, pid_t *table)
{
	t_philo	*ptr;
	long	i;

	i = -1;
	ptr = data->philo;
	while (ptr && ++i < data->nb_of_philo)
	{
		table[i] = fork();
		if (table[i] == -1)
		{
			write(2, "Error: fork\n", 12);
			free(table);
			return ;
		}
		if (table[i] == 0)
			start_child(&ptr);
		ptr = ptr->next;
	}
}

/*----------------------------------------------------------------*/

void	start_simulation(t_info *data, char **av)
{
	pid_t	*table;

	create_list(&data, av);
	destroy__sem(&data, 0);
	if (create__sem(&data, data->nb_of_philo))
	{
		table = malloc(data->nb_of_philo * sizeof(pid_t));
		if (!table)
			return ;
		init_time_sem(&data, data->nb_of_philo);
		create_childs(data, table);
		my_wait(table, data->nb_of_philo);
		free(table);
	}
	destroy__sem(&data, 1);
}
