/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:49:34 by amahla            #+#    #+#             */
/*   Updated: 2022/07/28 13:58:11 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_true(t_thread *th)
{
	pthread_mutex_lock(&th->philo->dead);
	if (th->philo->is_one_dead == TRUE)
	{
		pthread_mutex_unlock(&th->philo->dead);
		return (1);
	}
	th->philo->is_one_dead = TRUE;
	pthread_mutex_unlock(&th->philo->dead);
	return (0);
}
