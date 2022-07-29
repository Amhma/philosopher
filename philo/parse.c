/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:02:21 by amahla            #+#    #+#             */
/*   Updated: 2022/07/29 13:41:03 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && *(str + i))
		i++;
	return (i);
}

int	ft_atoi_format(char *str)
{
	unsigned int	nb;
	int				i;

	i = 0;
	nb = 0;
	while (str && *(str + i) == '0')
		i++;
	if (!str || !str[i] || ft_strlen(str + i) > 10)
		return (-1);
	if (!(*(str + i) >= '1' && *(str + i) <= '9'))
		return (-1);
	while (*(str + i) >= '0' && *(str + i) <= '9')
		nb = nb * 10 + str[i++] - 48;
	if (*(str + i))
		return (-1);
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}		

int	parse_philo(char **av, int ac, t_philo *philo)
{
	philo->nb_of_philo = ft_atoi_format(av[0]);
	philo->die_time = ft_atoi_format(av[1]);
	philo->eat_time = ft_atoi_format(av[2]);
	philo->sleep_time = ft_atoi_format(av[3]);
	if (ac == 6)
	{
		philo->times = ft_atoi_format(av[4]);
		if (philo->times == -1)
			return (1);
	}
	else
		philo->times = -1;
	if (philo->nb_of_philo == -1 || philo->die_time == -1
		|| philo->eat_time == -1 || philo->sleep_time == -1)
		return (1);
	philo->is_one_dead = FALSE;
	return (0);
}

int	ft_allocation(t_thread **philo, pthread_mutex_t **fork, int nb_of_philo)
{
	*philo = malloc(nb_of_philo * sizeof(t_thread));
	if (!*philo)
		return (1);
	*fork = malloc(nb_of_philo * sizeof(pthread_mutex_t));
	if (!*fork)
	{
		free(*philo);
		return (1);
	}
	return (0);
}
