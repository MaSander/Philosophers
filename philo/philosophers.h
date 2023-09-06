/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:53 by msander-          #+#    #+#             */
/*   Updated: 2023/08/21 20:23:33 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>

# define TAKE_A_FORK 1
# define EATING 2
# define SLEEPING 122
# define THINKING 420
# define DIED 666

typedef struct s_data {
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
	int				did_someone_die;
	long			life_start_time;
	pthread_mutex_t	*pancil;
}	t_data;

typedef struct s_philo {
	int				name;
	int				satisfied;
	long			last_food;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*lock_food_data;
	pthread_mutex_t	*lock_satisfy_data;

}	t_philo;

int		philosopher(t_data	*data);

void	*life(void *philo);

long	get_time_now(void);
void	ft_sleep(int miliseconds);
long	current_time(t_philo *philo);

void	*monitoring(void *philo_array);
int		philo_is_alive(t_philo *philo);

void	update_last_food(t_philo *philo);
long	get_last_food(t_philo *philo);
void	increment_satisfied(t_philo *philo);
int		get_satisfied(t_philo *philo);

int		did_someone_die(t_data *data);
void	register_death(t_data *data);

void	write_philo_action(t_philo *philo, int action);

void	exit_error(int exit_code, char *message_error);

int		ft_isalldigit(char *str);

void	*ft_calloc(size_t num, size_t size);

int		ft_atoi(const char *str);

#endif