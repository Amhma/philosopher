/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:12:15 by amahla            #+#    #+#             */
/*   Updated: 2022/07/28 14:28:49 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_dead(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->dead);
	if (philo->is_one_dead == TRUE)
		res = 1;
	pthread_mutex_unlock(&philo->dead);
	return (res);
}

long long	ft_get_time(void)
{
	long long		time;
	struct timeval	ref;

	gettimeofday(&ref, NULL);
	time = ref.tv_sec * 1000 + ref.tv_usec / 1000;
	return (time);
}

void	ft_usleep(long long time)
{
	long long	start_time;

	start_time = ft_get_time();
	while (ft_get_time() - start_time < time)
		usleep(50);
}

void	check_dead_fork(pthread_mutex_t *mutex1,
	pthread_mutex_t *mutex2)
{
	if (mutex1)
		pthread_mutex_unlock(mutex1);
	if (mutex2)
		pthread_mutex_unlock(mutex2);
}

int	thinking(t_thread *th, int i)
{
	if (print_action(4, i, th->philo, 0))
		return (1);
	if (th->philo->nb_of_philo % 2)
		ft_usleep((th->philo->die_time - th->philo->eat_time
				- th->philo->sleep_time) / 2);
	return (0);
}
