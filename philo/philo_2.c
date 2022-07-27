/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:21:47 by amahla            #+#    #+#             */
/*   Updated: 2022/07/27 19:43:33 by amahla           ###   ########.fr       */
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
