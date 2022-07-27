/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:12:15 by amahla            #+#    #+#             */
/*   Updated: 2022/07/26 20:56:55 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_fork(t_thread *th, int i)
{
	pthread_mutex_lock(th->fork + i);
	if (print_action(1, i, th, 0))
	{
		check_dead_fork(th, th->fork + i, NULL);
		return (1);
	}
//	printf("%lld %d has taken a fork\n", ft_get_time() - th->start_time, i + 1);
	if (i == 0)
	{
		pthread_mutex_lock(th->fork + th->nb_of_philo - 1);
		if (print_action(1, i, th, 0))
		{
			check_dead_fork(th, th->fork + i, th->fork + th->nb_of_philo - 1);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(th->fork + i - 1);
		if (print_action(1, i, th, 0))
		{
			check_dead_fork(th, th->fork + i, th->fork + i - 1);
			return (1);
		}
	}	
//	printf("%lld %d has taken a fork\n", ft_get_time() - th->start_time, i + 1);
	return (0);
}

int	odd_fork(t_thread *th, int i)
{
	pthread_mutex_lock(th->fork + i - 1);
	if (print_action(1, i, th, 0))
	{
		check_dead_fork(th, th->fork + i - 1, NULL);
		return (1);
	}
//	printf("%lld %d has taken a fork\n", ft_get_time() - th->start_time, i + 1);
	pthread_mutex_lock(th->fork + i);
	if (print_action(1, i, th, 0))
	{
		check_dead_fork(th, th->fork + i - 1, th->fork + i);
		return (1);
	}
//	printf("%lld %d has taken a fork\n", ft_get_time() - th->start_time, i + 1);
	return (0);
}

int	eating(t_thread *th, int i)
{
	if (!(i % 2))
	{
		if (even_fork(th, i))
			return (1);
	}
	else if (i % 2)
	{
		if (odd_fork(th, i))
			return (1);
	}
//	printf("%lld %d is eating\n", ft_get_time() - th->start_time, i + 1);
	if (print_action(2, i, th, 0))
		return (1);
	pthread_mutex_lock(&th->philo[i].last_time_eat);
	th->philo[i].last_eat = ft_get_time();
	pthread_mutex_unlock(&th->philo[i].last_time_eat);
	ft_usleep(th->eat_time);
	return (0);
}

int	sleepling(t_thread *th, int i)
{
//	(void)stroke;
	if (!(i % 2))
	{
		if (i == 0)
			pthread_mutex_unlock(th->fork + th->nb_of_philo - 1);
		else
			pthread_mutex_unlock(th->fork + i - 1);
		pthread_mutex_unlock(th->fork + i);
	}
	else if (i % 2)
	{
		pthread_mutex_unlock(th->fork + i);
		pthread_mutex_unlock(th->fork + i - 1);
	}
	pthread_mutex_lock(&th->philo[i].last_time_eat);
	if (th->philo[i].stroke > 0)
		th->philo[i].stroke -= 1;
	if (th->philo[i].stroke == 0)
		return (1);
	pthread_mutex_unlock(&th->philo[i].last_time_eat);
	if (print_action(3, i, th, 0))
		return (1);
//	printf("%lld %d is sleeping\n", ft_get_time() - th->start_time, i + 1);
	ft_usleep(th->sleep_time);
	return (0);
}

void	*routine(void *arg)
{
	t_thread	*th;
	int			i;

	th = (t_thread *)arg;
	pthread_mutex_lock(&th->process);
	i = th->current_philo++;
	if (th->set_time == FALSE)
	{
		th->start_time = ft_get_time();
		th->set_time = TRUE;
	}
	pthread_mutex_unlock(&th->process);
	if (i % 2)
		ft_usleep(th->eat_time / 2);
	pthread_mutex_lock(&th->philo[i].last_time_eat);
	th->philo[i].last_eat = ft_get_time();
	pthread_mutex_unlock(&th->philo[i].last_time_eat);
	while (!check_is_dead(th))
	{
		if (eating(th, i))
			return (arg);
		if (sleepling(th, i))
		{
//			pthread_mutex_unlock(&th->philo[i].last_time_eat);
			return (arg);
		}
		if (thinking(th, i))
			return (arg);
	}
	return (arg);
}
