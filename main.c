/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:28 by msander-          #+#    #+#             */
/*   Updated: 2023/08/03 19:11:08 by msander-         ###   ########.fr       */
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
	pthread_mutex_init(&data->pancil, NULL);
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
		pthread_mutex_init(&philo[i].left_fork, NULL);
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

int	give_life(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	data->life_start_time = get_time_now();
	while (++i < data->num_philo)
		pthread_create(&philo[i].thread, NULL, &life, &philo[i]);
	i = -1;
	while (++i < data->num_philo)
		pthread_join(philo[i].thread, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	check_args(argc, argv);
	init_args(&data, argc, argv);
	philo = malloc(sizeof(t_philo) * data.num_philo);
	init_philo(&data, philo);
	give_life(&data, philo);
	while (i < data.num_philo)
	{
		pthread_mutex_destroy(&philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&data.pancil);
	free(philo);
	return (0);
}
