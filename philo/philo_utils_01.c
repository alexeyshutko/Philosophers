/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:44:48 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/06/20 15:45:25 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

void	print_unsigned_num(unsigned long int number, int base, char a)
{
	char	z;

	if (number >= (unsigned long)base)
		print_unsigned_num(number / base, base, a);
	z = number % base;
	if (z > 9)
		z = z - 10 + a;
	else
		z = z + '0';
	write(1, &z, 1);
}

unsigned long	get_time_to_mls(void)
{
	struct timeval	tp;
	unsigned long	res;

	gettimeofday(&tp, NULL);
	res = (unsigned long)(tp.tv_sec * 1000 + tp.tv_usec / 1000);
	return (res);
}

int	mutex_section(t_data *data)
{
	if (pthread_mutex_init(&(data->check_eat_times), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->std_out));
		pthread_mutex_destroy(&(data->last_time_eating));
		free_malloc(data);
		return (error("mutex error\n"));
	}
	if (pthread_mutex_init(&(data->dead_check), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->check_eat_times));
		pthread_mutex_destroy(&(data->std_out));
		pthread_mutex_destroy(&(data->last_time_eating));
		free_malloc(data);
		return (error("mutex error\n"));
	}
	return (1);
}

int	philo_and_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->input_data[PHIL_NB])
	{
		data->phil_treads[i].num = i + 1;
		data->phil_treads[i].data = data;
		data->phil_treads[i].last_time_eat = data->start;
		data->phil_treads[i].eat_times = 0;
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(data->forks + i);
			return (error("mutex error\n"));
		}
		if (i != 0)
		{
			data->phil_treads[i].right_fork = data->forks + i - 1;
			data->phil_treads[i].left_fork = data->forks + i;
		}
	}
		data->phil_treads[0].right_fork = data->forks + i - 1;
		data->phil_treads[0].left_fork = data->forks;
	return (1);
}
