/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:53 by msander-          #+#    #+#             */
/*   Updated: 2023/08/01 14:20:23 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <pthread.h>
 
typedef struct s_data {
	int num_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_philo_must_eat;
	int did_someone_die;
} t_data;

typedef struct s_philo {
	int				name;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				satisfied;

} t_philo;

int	philo_life(t_data *data, t_philo *philo);

int	ft_atoi(const char *str);

void check_args(int argv, char *argc[]);

void exit_error(int exit_code, char *message_error);


#endif