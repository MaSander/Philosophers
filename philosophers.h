/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:53 by msander-          #+#    #+#             */
/*   Updated: 2023/08/03 19:09:49 by msander-         ###   ########.fr       */
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
	pthread_mutex_t	pancil;
}	t_data;

typedef struct s_philo {
	int				name;
	int				satisfied;
	long			last_food;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;

}	t_philo;

void	*life(void *philo);

long	get_time_now(void);
void	ft_sleep(int miliseconds);
long	calculate_current_time(t_philo *philo);

void	write_philo_action(t_philo *philo, int action);

void	check_args(int argv, char *argc[]);

void	exit_error(int exit_code, char *message_error);

void	*ft_calloc(size_t num, size_t size);

int		ft_atoi(const char *str);

#endif