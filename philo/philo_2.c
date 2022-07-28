/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:21:47 by amahla            #+#    #+#             */
/*   Updated: 2022/07/28 13:59:29 by amahla           ###   ########.fr       */
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
	ft_usleep(th->philo->eat_time / 2);
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
	long long	time_death;

	th = (t_thread *)arg;
	i = 0;
	while (1)
	{
		time_death = ft_get_time();
		if (check_last_eat(th, th->philo, i, time_death))
		{
			if (check_dead_true(th))
				break ;
			if (th->philo->times == -1 || !check_stroke(th, i))
				print_action(5, i, th->philo, time_death);
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
	long long	time_death;

	th = (t_thread *)arg;
	i = 100;
	while (th->philo->nb_of_philo > 100)
	{
		time_death = ft_get_time();
		if (check_last_eat(th, th->philo, i, time_death))
		{
			if (check_dead_true(th))
				break ;
			if (th->philo->times == -1 || !check_stroke(th, i))
				print_action(5, i, th->philo, time_death);
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
	pthread_t	monitor[2];

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
