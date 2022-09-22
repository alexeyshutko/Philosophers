/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:44:19 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/06/20 15:45:30 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	life_check(int *i, t_data *data)
{
	*i = -1;
	while (++(*i) < data->input_data[PHIL_NB])
	{
		pthread_mutex_lock(&data->check_eat_times);
		if (data->phil_treads[*i].eat_times < \
		data->input_data[EAT_TIMES])
		{
			pthread_mutex_unlock(&data->check_eat_times);
			break ;
		}
		pthread_mutex_unlock(&data->check_eat_times);
	}
}

int	is_dead_check(t_data *data)
{
	pthread_mutex_lock(&(data->dead_check));
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&(data->dead_check));
		return (1);
	}
	if (data->eats_all == 1)
	{
		pthread_mutex_unlock(&(data->dead_check));
		return (-1);
	}
	pthread_mutex_unlock(&(data->dead_check));
	return (0);
}

int	check_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->input_data[PHIL_NB])
	{
		pthread_mutex_lock(&(data->last_time_eating));
		if (get_time_to_mls() - data->phil_treads[i].last_time_eat \
		>= (unsigned long)data->input_data[DIE_TIME])
		{
			pthread_mutex_lock(&data->dead_check);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_check);
			print_action("died", &(data->phil_treads[i]), 1);
		}
		pthread_mutex_unlock(&(data->last_time_eating));
		usleep(100);
		if (is_dead_check(data) > 0)
			return (-1);
	}
	return (1);
}

int	check_dead_and_eat_all(t_data *data)
{
	int	i;

	while (1)
	{
		if (check_death(data) < 0)
			return (0);
		if (is_dead_check(data) != 0)
			return (0);
		if (data->input_data[EAT_TIMES] >= 0)
		{
			life_check(&i, data);
			if (i == data->input_data[PHIL_NB])
			{
				pthread_mutex_lock(&(data->dead_check));
				data->eats_all = 1;
				pthread_mutex_unlock(&(data->dead_check));
			}
		}
	}
	return (0);
}
