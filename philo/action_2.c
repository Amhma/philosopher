/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:12:15 by amahla            #+#    #+#             */
/*   Updated: 2022/07/27 11:32:52 by ammah            ###   ########.fr       */
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

void	check_dead_fork(t_thread *th, pthread_mutex_t *mutex1,
	pthread_mutex_t *mutex2)
{
	(void)th;
/*	int	res;


	res = 0;
	pthread_mutex_lock(&th->dead);
	if (th->is_one_dead == TRUE)
	{*/
		if (mutex1)
			pthread_mutex_unlock(mutex1);
		if (mutex2)
			pthread_mutex_unlock(mutex2);
//		res = 1;
//	}
//	pthread_mutex_unlock(&th->dead);
//	return (res);
}

int	thinking(t_thread *th, int i)
{
//	if (check_dead_fork(th, NULL, NULL))
//		return (1);
	if (print_action(4, i, th, 0))
		return (1);
//	printf("%lld %d is thinking\n", ft_get_time() - th->start_time, i + 1);
	if (th->nb_of_philo % 2)
		ft_usleep(1);
	return (0);
}	
