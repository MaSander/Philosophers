/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:28 by msander-          #+#    #+#             */
/*   Updated: 2023/08/03 02:48:36 by msander-         ###   ########.fr       */
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
	data->pancil = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (argc == 6)
		data->num_philo_must_eat = ft_atoi(argv[5]);
}

void	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo[i].name = (i + 1);
		philo[i].satisfied = 0;
		philo[i].data = data;
		philo[i].last_food = 0;
		philo[i].left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		i++;
	}
	i--;
	philo->right_fork = philo[i].left_fork;
	while (i)
	{
		philo[i].right_fork = philo[i - 1].left_fork;
		i--;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	int		i;
	int		result;

	i = 0;
	check_args(argc, argv);
	init_args(&data, argc, argv);
	philo = malloc(sizeof(t_philo) * data.num_philo);
	init_philo(&data, philo);
	result = philo_life(&data, philo);
	while (i < data.num_philo)
	{
		free(philo[i].left_fork);
		i++;
	}
	free(philo);
	return (result);
}
