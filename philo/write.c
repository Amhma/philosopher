/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:56:03 by amahla            #+#    #+#             */
/*   Updated: 2022/07/27 19:51:22 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nblen(long long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

void	ft_putnbr(long long nb, char *str, int size)
{
	if (nb >= 10)
		ft_putnbr(nb / 10, str, size - 1);
	str[size] = nb % 10 + 48;
}

void	ft_write(char *str, long long time, int pos)
{
	char	res[35];
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = nblen(time);
	ft_putnbr(time, res, size - 1);
	i += size;
	*(res + i++) = ' ';
	size = nblen((long long)pos);
	ft_putnbr((long long)pos, res + i, size - 1);
	i += size;
	*(res + i++) = ' ';
	while (*(str + j))
	{
		*(res + i) = *(str + j);
		i++;
		j++;
	}
	*(res + i) = '\0';
	write(1, res, ft_strlen(res));
}
