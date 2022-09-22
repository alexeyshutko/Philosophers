/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:44:56 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/06/20 15:45:23 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define PHIL_NB 0
# define DIE_TIME 1
# define EAT_TIME 2
# define SLEEP_TIME 3
# define EAT_TIMES 4

typedef struct s_phil_treads
{
	pthread_t		thread;
	int				num;
	void			*data;
	void			*right_fork;
	void			*left_fork;
	int				eat_times;
	unsigned long	last_time_eat;
}t_phil_treads;

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	int				dead;
	t_mutex			dead_check;
	int				eats_all;
	int				input_data[6];
	unsigned long	start;
	t_phil_treads	*phil_treads;
	t_mutex			*forks;
	t_mutex			std_out;
	t_mutex			last_time_eating;
	t_mutex			check_eat_times;
}t_data;

int				error(char *str);
int				initializer(t_data *data, char **argv, int argc);
int				get_check_argv(t_data *data, char **av, int ac);
int				malloc_box(t_data *data);
int				init_mutex(t_data *data);
void			free_malloc(t_data *data);
int				mutex_section(t_data *data);
int				philo_and_forks(t_data *data);
unsigned long	get_time_to_mls(void);
void			all_clean(t_data *data);
int				check_dead_and_eat_all(t_data *data);
int				check_death(t_data *data);
int				print_action(char *s, t_phil_treads *pthread, int dead);
int				is_dead_check(t_data *data);
void			print_unsigned_num(unsigned long int number, int base, char a);
void			ft_putstr(char *s);
void			eating(t_phil_treads *phil_thread, t_data *data);
void			my_sleep(unsigned long mls);
void			lock_forks(t_phil_treads *phil_thread);
void			*act(void *args);
int				ft_atoi(const char *str, int *result);
int				ft_strlen(const char *s);
#endif