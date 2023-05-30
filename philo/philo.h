/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:41:40 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/17 17:04:21 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	long			nb;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	long			nb_times_eat;
	long			time_passed;
	long			last_time_eat;
	struct timeval	start_time;
	struct timeval	first_start;
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*printf;
	struct s_philo	*next;
}	t_philo;

typedef struct s_info
{
	long			nb_of_philo;
	pthread_mutex_t	mutex;
	pthread_mutex_t	printf;
	long			nb_must_eat;
	t_philo			*philo;
}	t_info;

long			ft_atoi(const char *str);
long			get_cur_time(t_philo **lst, int if_eating);
void			start_simulation(t_info *data, char **av);
void			ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo			*ft_lstnew(int id, char **str, struct timeval s_t, int nb);
void			ft_lstclear(t_philo **lst, long nb);
void			my_usleep(long miliseconds, t_philo **lst);
void			create_list(t_info **data, char **av);
void			point_to_mutex(t_info **data);
void			check_death(t_info **data);

#endif