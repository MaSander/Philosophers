/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:30:23 by msander-          #+#    #+#             */
/*   Updated: 2023/08/07 11:45:14 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_args(t_data *data, int argc, char *argv[])
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->did_someone_die = 0;
	data->life_start_time = 0;
	data->num_philo_must_eat = -1;
	data->pancil = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->pancil, NULL);
	if (argc == 6)
		data->num_philo_must_eat = ft_atoi(argv[5]);
}

int main(int argc, char *argv[])
{
	t_data data;

	check_args(argc, argv);
	init_args(&data, argc, argv);
	philosopher(&data);
	return (0);
}