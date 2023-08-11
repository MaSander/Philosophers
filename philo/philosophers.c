/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:28 by msander-          #+#    #+#             */
/*   Updated: 2023/08/07 11:45:26 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].left_fork, NULL);
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

int	give_life(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	data->life_start_time = get_time_now();
	while (++i < data->num_philo)
		pthread_create(&philos[i].thread, NULL, &life, &philos[i]);
	i = -1;
	monitoring(data, philos);
	while (++i < data->num_philo)
		pthread_join(philos[i].thread, NULL);
	return (0);
}

int	philosopher(t_data	*data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->num_philo);
	init_philo(data, philos);
	give_life(data, philos);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(philos[i].left_fork);
		free(philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(data->pancil);
	free(data->pancil);
	free(philos);
	return (0);
}