/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:44:31 by amahla            #+#    #+#             */
/*   Updated: 2022/07/27 11:30:50 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stroke(t_thread *th, int i)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&th[i].last_time_eat);
	if (th[i].stroke == -1)
		res = 0;
	else if (th[i].stroke <= 0)
		res = 1;
	pthread_mutex_unlock(&th[i].last_time_eat);
	return (res);
}

int	print_action(int action, int i, t_philo *philo, long long time_death)
{
	pthread_mutex_lock(&philo->print);
	if (action >= 1 && action <= 4)
	{
		if (!check_is_dead(philo))
		{
			if (action == 1)
				printf("%lld %d has taken a fork\n", ft_get_time() - philo->start_time, i + 1);
			else if (action == 2)
				printf("%lld %d is eating\n", ft_get_time() - philo->start_time, i + 1);
			else if (action == 3)
				printf("%lld %d is sleeping\n", ft_get_time() - philo->start_time, i + 1);
			else if (action == 4)
				printf("%lld %d is thinking\n", ft_get_time() - philo->start_time, i + 1);
			pthread_mutex_unlock(&philo->print);
			return (0);
		}
		pthread_mutex_unlock(&philo->print);
		return (1);
	}
	else if (action == 5)
		printf("%lld %d died\n", time_death - philo->start_time, i + 1);
	pthread_mutex_unlock(&philo->print);
	return (0);
}
