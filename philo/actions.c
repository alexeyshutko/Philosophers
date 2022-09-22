/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:44:11 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/06/20 15:45:31 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_phil_treads *phil_thread)
{
	pthread_mutex_lock(phil_thread->right_fork);
	print_action("has taken a fork", phil_thread, 0);
	pthread_mutex_lock(phil_thread->left_fork);
	print_action("has taken a fork", phil_thread, 0);
}

void	my_sleep(unsigned long mls)
{
	struct timeval	tp;
	unsigned long	start;

	gettimeofday(&tp, NULL);
	start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	while ((tp.tv_sec * 1000 + tp.tv_usec / 1000) - start < mls)
	{
		usleep(50);
		gettimeofday(&tp, NULL);
	}
}

void	eating(t_phil_treads *phil_thread, t_data *data)
{
	lock_forks(phil_thread);
	pthread_mutex_lock(&(data->last_time_eating));
	print_action("is eating", phil_thread, 0);
	phil_thread->last_time_eat = get_time_to_mls();
	pthread_mutex_unlock(&(data->last_time_eating));
	my_sleep(data->input_data[EAT_TIME]);
	pthread_mutex_lock(&data->check_eat_times);
	phil_thread->eat_times += 1;
	pthread_mutex_unlock(&data->check_eat_times);
	pthread_mutex_unlock(phil_thread->right_fork);
	pthread_mutex_unlock(phil_thread->left_fork);
}

void	*act(void *args)
{
	t_phil_treads	*phil_thread;
	t_data			*data;

	phil_thread = (t_phil_treads *)args;
	data = (t_data *)phil_thread->data;
	if (data->input_data[PHIL_NB] == 1)
	{
		print_action("has taken a fork", phil_thread, 0);
		while (is_dead_check(data) == 0)
			;
		return (NULL);
	}
	if ((phil_thread->num) % 2 != 0)
		usleep(8000);
	while (1)
	{
		if (is_dead_check(data))
			return (NULL);
		eating(phil_thread, data);
		print_action("is sleeping", phil_thread, 0);
		my_sleep(data->input_data[SLEEP_TIME]);
		print_action("is thinking", phil_thread, 0);
	}
	return (NULL);
}

int	print_action(char *s, t_phil_treads *pthread, int dead)
{
	t_data	*data;

	data = (t_data *)pthread->data;
	pthread_mutex_lock(&(data->std_out));
	if (is_dead_check(data) && dead == 0)
	{
		pthread_mutex_unlock(&(data->std_out));
		return (0);
	}
	print_unsigned_num(get_time_to_mls() - data->start, 10, 'a');
	write(1, " ", 1);
	print_unsigned_num(pthread->num, 10, 'a');
	write(1, " ", 1);
	ft_putstr(s);
	write(1, "\n", 1);
	pthread_mutex_unlock(&(data->std_out));
	return (0);
}
