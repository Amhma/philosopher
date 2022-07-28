/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:21:47 by amahla            #+#    #+#             */
/*   Updated: 2022/07/28 13:27:15 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(t_thread *th, t_philo *philo)
{
	int	i;

	i = 0;
	philo->start_time = ft_get_time();
	while (i < philo->nb_of_philo)
	{
		if (pthread_create(&th[i].thread, NULL, &routine, th + i))
		{
			pthread_mutex_unlock(&philo->process);
			return (1);
		}
		i += 2;
	}
	ft_usleep(th->philo->eat_time);
	i = 1;
	while (i < philo->nb_of_philo)
	{
		if (pthread_create(&th[i].thread, NULL, &routine, th + i))
		{
			pthread_mutex_unlock(&philo->process);
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	process_monitor(void)
{
	usleep(50);
	return (0);
}

void	*routine_1(void *arg)
{
	t_thread	*th;
	int			i;

	th = (t_thread *)arg;
	i = 0;
	while (1)
	{
		th->philo->time_death = ft_get_time();
		if (check_last_eat(th, th->philo, i, th->philo->time_death))
		{
			pthread_mutex_lock(&th->philo->dead);
			if (th->philo->is_one_dead == TRUE)
				break ;
			th->philo->is_one_dead = TRUE;
			pthread_mutex_unlock(&th->philo->dead);
			if (th->philo->times == -1 || !check_stroke(th, i))
				print_action(5, i, th->philo, th->philo->time_death);
			break ;
		}
		if (i == 99 || i++ == th->philo->nb_of_philo - 1)
		{
			usleep(50);
			i = 0;
		}
	}
	return (arg);
}

void	*routine_2(void *arg)
{
	t_thread	*th;
	int			i;

	th = (t_thread *)arg;
	i = 100;
	while (th->philo->nb_of_philo > 100)
	{
		th->philo->time_death = ft_get_time();
		if (check_last_eat(th, th->philo, i, th->philo->time_death))
		{
			pthread_mutex_lock(&th->philo->dead);
			if (th->philo->is_one_dead == TRUE)
				break ;
			th->philo->is_one_dead = TRUE;
			pthread_mutex_unlock(&th->philo->dead);
			if (th->philo->times == -1 || !check_stroke(th, i))
				print_action(5, i, th->philo, th->philo->time_death);
			break ;
		}
		if (i == 199 || i++ == th->philo->nb_of_philo - 1)
		{
			usleep(50);
			i = 100;
		}
	}
	return (arg);
}


int	monitor(t_thread *th)
{
	pthread_t monitor[4];

	if (pthread_create(monitor, NULL, &routine_1, th))
		return (1);
	if (pthread_create(monitor + 1, NULL, &routine_2, th))
		return (1);
	if (pthread_join(monitor[1], NULL))
		return (1);
	if (pthread_join(monitor[0], NULL))
		return (1);
	return (0);
}
