/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:53 by msander-          #+#    #+#             */
/*   Updated: 2023/08/02 15:34:54 by msander-         ###   ########.fr       */
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

typedef struct s_data {
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_philo_must_eat;
	int		did_someone_die;
	long	life_start_time;
}	t_data;

typedef struct s_philo {
	int				name;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				satisfied;

}	t_philo;

int		philo_life(t_data *data, t_philo *philo);

long	get_time_now(void);
long	calculate_philo_moment(void *philo);

int		ft_atoi(const char *str);

void	check_args(int argv, char *argc[]);

void	exit_error(int exit_code, char *message_error);

#endif