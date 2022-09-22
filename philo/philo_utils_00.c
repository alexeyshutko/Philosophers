/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:44:44 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/06/20 15:45:26 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&(data->std_out), NULL) != 0)
	{
		free_malloc(data);
		return (error("mutex error\n"));
	}
	if (pthread_mutex_init(&(data->last_time_eating), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->std_out));
		free_malloc(data);
		return (error("mutex error\n"));
	}
	return (mutex_section(data));
}

int	malloc_box(t_data *data)
{
	data->phil_treads = (t_phil_treads *)malloc(\
	sizeof(t_phil_treads) * data->input_data[PHIL_NB]);
	if (!(data->phil_treads))
		return (error("malloc memory fail\n"));
	data->forks = (t_mutex *) malloc(sizeof(t_mutex) \
	* data->input_data[PHIL_NB]);
	if (!(data->forks))
	{
		free(data->phil_treads);
		return (error("malloc memory fail\n"));
	}
	return (1);
}

int	get_check_argv(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	if (ac != 6)
		data->input_data[EAT_TIMES] = -1;
	while (++i < ac)
	{
		if (ft_atoi(av[i], &(data->input_data[i - 1])) < 0)
			return (error("wrong param\n"));
		if (data->input_data[i - 1] <= 0)
			return (error("wrong param\n"));
	}
	return (1);
}

int	error(char *str)
{
	if (!str)
		return (-2);
	write(1, str, ft_strlen(str));
	return (-1);
}

int	initializer(t_data *data, char **av, int ac)
{
	data->dead = 0;
	data->eats_all = 0;
	if (get_check_argv(data, av, ac) < 0)
		return (-1);
	if (malloc_box(data) < 0)
		return (-1);
	if (init_mutex(data) < 0)
		return (-1);
	if (philo_and_forks(data) < 0)
	{
		pthread_mutex_destroy(&(data->std_out));
		pthread_mutex_destroy(&(data->last_time_eating));
		pthread_mutex_destroy(&(data->check_eat_times));
		free_malloc(data);
		return (-1);
	}
	return (1);
}
