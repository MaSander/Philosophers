/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:53 by msander-          #+#    #+#             */
/*   Updated: 2023/07/30 20:06:59 by msander-         ###   ########.fr       */
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
} t_data;

typedef struct s_philo {
    pthread_t thread;
} t_philo;

int	ft_atoi(const char *str);

void check_args(int argv, char *argc[]);

void exit_error(int exit_code, char *message_error);


#endif