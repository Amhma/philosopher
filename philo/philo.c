/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:12:15 by amahla            #+#    #+#             */
/*   Updated: 2022/07/27 11:38:47 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	check_last_eat(t_thread *th, t_philo *philo, int i, long long death_time)
{
	long long	res;

	res = 0;
	pthread_mutex_lock(&th[i].last_time_eat);
	if (!th[i].last_eat)
		res = death_time - philo->start_time;
	else
		res = death_time - th[i].last_eat;
	pthread_mutex_unlock(&th[i].last_time_eat);
	if (res <= (long long)philo->die_time)
		return (0);
	return (1);
}

int	init_mutex(t_thread *th, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philo->process, NULL);
	pthread_mutex_init(&philo->print, NULL);
	pthread_mutex_init(&philo->dead, NULL);
	while (i < philo->nb_of_philo)
	{
		pthread_mutex_init(philo->fork + i, NULL);
		pthread_mutex_init(&th[i++].last_time_eat, NULL);
	}
	i = 0;
	pthread_mutex_lock(&philo->process);
	while (i < philo->nb_of_philo)
	{
		if (pthread_create(&th[i].thread, NULL, &routine, th + i))
		{
			pthread_mutex_unlock(&philo->process);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->process);
	philo->start_time = ft_get_time();
	return (0);
}

int	destroy_mutex(t_thread *th, t_philo *philo)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < philo->nb_of_philo)
	{
		if (pthread_join(th[i++].thread, NULL))
			res = 1;;
	}
	i = 0;
	while (i < philo->nb_of_philo)
	{
		pthread_mutex_destroy(philo->fork + i);
		pthread_mutex_destroy(&th[i++].last_time_eat);
	}
	pthread_mutex_destroy(&philo->process);
	pthread_mutex_destroy(&philo->dead);
	pthread_mutex_destroy(&philo->print);
	return (res);
}

int	philo_process(t_thread *th, t_philo *philo)
{
	int			i;
	long long	time_death;

	i = 0;
	if (init_mutex(th, th->philo))
		return (1);
	while (1)
	{
		time_death = ft_get_time();
		if (check_last_eat(th, philo, i, time_death))
		{
			pthread_mutex_lock(&philo->dead);
			philo->is_one_dead = TRUE;
			pthread_mutex_unlock(&philo->dead);
			if (philo->times == -1 || !check_stroke(th, i))
				print_action(5, i, philo, time_death);
//				printf("%lld %d died\n", time_death - th->start_time, i + 1);
			break ;
		}
		if (i++ == philo->nb_of_philo - 1)
		{
			usleep(50);
			i = 0;
		}
	}
	if (destroy_mutex(th, th->philo))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	t_thread	*th;
	int			i;
	int			res;

	i = 0;
	res = 0;
	if (ac < 5 || ac > 6)
		return (1);
	if (parse_philo(av + 1, ac, &philo))
		return (1);
	if (ft_allocation(&th, &philo.fork, philo.nb_of_philo))
		return (1);
	while (i < philo.nb_of_philo)
	{
		th[i].philo = &philo;
		th[i].current_philo = i;
		th[i].stroke = philo.times;
		th[i].last_eat = 0;
	}
	if (philo_process(th, &philo))
		res = 1;
	free(philo.fork);
	free(th);
	return (res);
}
