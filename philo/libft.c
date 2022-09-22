/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:44:32 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/06/20 15:45:28 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		++i;
	return (i);
}

int	ft_atoi(const char *str, int *result)
{
	int		i;
	long	res;

	i = -1;
	res = 0;
	if (!str || *str == '\0')
		return (-1);
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res *= 10;
		res += str[i] - '0';
		if (res > 2147483647)
			return (-1);
	}
	*result = (int)res;
	return (1);
}
