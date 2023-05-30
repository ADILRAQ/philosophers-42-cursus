/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:58:18 by araqioui          #+#    #+#             */
/*   Updated: 2023/05/17 10:43:11 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_length(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long n)
{
	char	*str;
	int		length;
	int		i;
	long	nb;

	nb = n;
	length = ft_length(nb);
	str = malloc((length + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[length - (i++) - 1] = (nb % 10) + 48;
		nb /= 10;
	}
	str[length] = '\0';
	return (str);
}
