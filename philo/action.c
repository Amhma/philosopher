/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:12:15 by amahla            #+#    #+#             */
/*   Updated: 2022/07/27 15:26:20 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->fork + i);
	if (print_action(1, i, philo, 0))
	{
		check_dead_fork(philo->fork + i, NULL);
		return (1);
	}
	if (i == 0)
	{
		pthread_mutex_lock(philo->fork + philo->nb_of_philo - 1);
		if (print_action(1, i, philo, 0))
		{
			check_dead_fork(philo->fork + i, philo->fork + philo->nb_of_philo - 1);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(philo->fork + i - 1);
		if (print_action(1, i, philo, 0))
		{
			check_dead_fork(philo->fork + i, philo->fork + i - 1);
			return (1);
		}
	}	
	return (0);
}

int	odd_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->fork + i - 1);
	if (print_action(1, i, philo, 0))
	{
		check_dead_fork(philo->fork + i - 1, NULL);
		return (1);
	}
	pthread_mutex_lock(philo->fork + i);
	if (print_action(1, i, philo, 0))
	{
		check_dead_fork(philo->fork + i - 1, philo->fork + i);
		return (1);
	}
	return (0);
}

int	eating(t_thread *th, t_philo *philo, int i)
{
	if (!(i % 2))
	{
		if (even_fork(philo, i))
			return (1);
	}
	else if (i % 2)
	{
		if (odd_fork(philo, i))
			return (1);
	}
	if (print_action(2, i, philo, 0))
		return (1);
	pthread_mutex_lock(&th->last_time_eat);
	th->last_eat = ft_get_time();
	pthread_mutex_unlock(&th->last_time_eat);
	ft_usleep(philo->eat_time);
	return (0);
}

int	sleepling(t_thread *th, t_philo *philo, int i)
{
	if (!(i % 2))
	{
		if (i == 0)
			pthread_mutex_unlock(philo->fork + philo->nb_of_philo - 1);
		else
			pthread_mutex_unlock(philo->fork + i - 1);
		pthread_mutex_unlock(philo->fork + i);
	}
	else if (i % 2)
	{
		pthread_mutex_unlock(philo->fork + i);
		pthread_mutex_unlock(philo->fork + i - 1);
	}
	pthread_mutex_lock(&th->last_time_eat);
	if (th->stroke > 0)
		th->stroke -= 1;
	if (th->stroke == 0)
		return (1);
	pthread_mutex_unlock(&th->last_time_eat);
	if (print_action(3, i, philo, 0))
		return (1);
	ft_usleep(philo->sleep_time);
	return (0);
}

void	*routine(void *arg)
{
	t_thread	*th;
	int			i;

	th = (t_thread *)arg;
	i = th->current_philo;
//	pthread_mutex_lock(&th->philo->process);
//	pthread_mutex_unlock(&th->philo->process);
	if (i % 2)
		ft_usleep(th->philo->eat_time);
	while (!check_is_dead(th->philo))
	{
		if (eating(th, th->philo, i))
			return (arg);
		if (sleepling(th, th->philo, i))
			return (arg);
		if (thinking(th, i))
			return (arg);
	}
	return (arg);
}
