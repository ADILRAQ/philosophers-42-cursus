/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:41:07 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/17 17:27:09 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int id, char **str, struct timeval s_t, int nb)
{
	t_philo			*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->nb = id;
	new->time_passed = 0;
	new->nb_must_eat = nb;
	new->last_time_eat = 0;
	new->nb_times_eat = 0;
	new->time_to_die = ft_atoi(str[2]);
	new->time_to_eat = ft_atoi(str[3]);
	new->time_to_sleep = ft_atoi(str[4]);
	new->first_start = s_t;
	new->next = NULL;
	return (new);
}

/*----------------------------------------------------------------*/

static t_philo	*ft_lstlast(t_philo *lst)
{
	t_philo	*ptr;

	ptr = lst;
	while (ptr->next != lst)
		ptr = ptr->next;
	return (ptr);
}

/*----------------------------------------------------------------*/

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*ptr;

	if (!lst || !new)
		return ;
	ptr = *lst;
	if (*lst)
	{
		ptr = ft_lstlast(ptr);
		ptr->next = new;
		new->next = *lst;
	}
	else
	{
		*lst = new;
		new->next = *lst;
	}
}

/*----------------------------------------------------------------*/

void	ft_lstclear(t_philo **lst, long nb)
{
	t_philo	*ptr;
	long	i;

	if (!lst || !(*lst))
		return ;
	ptr = *lst;
	i = -1;
	while (++i < nb)
	{
		ptr = ptr->next;
		free(*lst);
		*lst = ptr;
	}
	lst = NULL;
}

/*----------------------------------------------------------------*/

void	create_list(t_info **data, char **av)
{
	struct timeval	start_time;
	long			i;

	(*data)->philo = NULL;
	(*data)->nb_of_philo = ft_atoi(av[1]);
	(*data)->nb_must_eat = -1;
	if (av[5])
		(*data)->nb_must_eat = ft_atoi(av[5]);
	i = 0;
	gettimeofday(&start_time, NULL);
	while (++i <= (*data)->nb_of_philo)
		ft_lstadd_back(&(*data)->philo,
			ft_lstnew(i, av, start_time, (*data)->nb_must_eat));
}
