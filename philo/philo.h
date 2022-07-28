/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:26:54 by amahla            #+#    #+#             */
/*   Updated: 2022/07/28 13:56:03 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

enum e_boolen
{
	TRUE,
	FALSE,
};

typedef struct s_time
{
	struct timeval	ref;
	struct timeval	actual;
}				t_time;

typedef struct s_thread
{
	pthread_t		thread;
	pthread_mutex_t	last_time_eat;
	int				current_philo;
	long long		last_eat;
	int				stroke;
	struct s_philo	*philo;
}				t_thread;

typedef struct s_philo
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	process;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				times;
	int				nb_of_philo;
	int				is_one_dead;
	long long		start_time;
	long long		time_death;
}				t_philo;

//			philo.c
long long	check_last_eat(t_thread *th, t_philo *philo, int i,
				long long death_time);

//			philo_2.c
int			start_philo(t_thread *th, t_philo *philo);
int			process_monitor(void);
void		*routine_1(void *arg);
void		*routine_2(void *arg);
int			monitor(t_thread *th);

//			parse.c
int			ft_strlen(char *str);
int			parse_philo(char **av, int ac, t_philo *philo);
int			ft_allocation(t_thread **philo, pthread_mutex_t **fork,
				int nb_of_philo);

//			action.c
long long	ft_get_time(void);
void		*routine(void *arg);

//			action_2.c
int			check_is_dead(t_philo *philo);
long long	ft_get_time(void);
void		ft_usleep(long long time);
void		check_dead_fork(pthread_mutex_t *mutex1,
				pthread_mutex_t *mutex2);

//			action_3.c
void		is_one_philo(t_thread *th, t_philo *philo);

int			thinking(t_thread *th, int i);

//			utils.c
int			check_stroke(t_thread *th, int i);
int			print_action(int action, int i, t_philo *philo,
				long long time_death);

//			write.c
void		ft_write(char *str, long long time, int i);

//			check.c
int			check_dead_true(t_thread *th);
#endif
