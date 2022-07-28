/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:11:01 by amahla            #+#    #+#             */
/*   Updated: 2022/07/28 12:17:11 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_one_philo(t_thread *th, t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	print_action(4, 0, th->philo, 0);
	while (!check_is_dead(philo))
		usleep(50);
	pthread_mutex_unlock(philo->fork);
}
