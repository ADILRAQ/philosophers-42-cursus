/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:56:23 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/22 15:53:40 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	long			nb;
	char			*str;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	long			nb_times_eat;
	long			time_passed;
	long			last_time_eat;
	struct timeval	start_time;
	struct timeval	first_start;
	sem_t			*fork;
	sem_t			*printf;
	sem_t			*eat;
	struct s_philo	*next;
}	t_philo;

typedef struct s_info
{
	long			nb_of_philo;
	long			nb_must_eat;
	sem_t			*sem;
	sem_t			*printf;
	t_philo			*philo;
}	t_info;

void			start_simulation(t_info *data, char **av);
void			create_list(t_info **data, char **av);
long			ft_atoi(const char *str);
long			get_cur_time(t_philo **lst, int if_eating);
void			my_usleep(long miliseconds, t_philo **lst);
void			ft_lstclear(t_philo **lst, long nb);
char			*ft_itoa(long n);
void			my_wait(int *tab, long nb_philo);
int				create__sem(t_info **data, long nb);
void			destroy__sem(t_info **data, int choose);
int				r_u_dead(t_philo *lst);
void			init_time_sem(t_info **data, long nb);

#endif