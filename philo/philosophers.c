/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:28 by msander-          #+#    #+#             */
/*   Updated: 2023/08/13 02:40:04 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	did_someone_die(t_data *data)
{
	int	someone_die;

	pthread_mutex_lock(data->pancil);
	someone_die = data->did_someone_die;
	pthread_mutex_unlock(data->pancil);
	return (someone_die);
}

void	register_death(t_data *data)
{
	pthread_mutex_lock(data->pancil);
	data->did_someone_die = 1;
	pthread_mutex_unlock(data->pancil);
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
		philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].left_fork, NULL);
		philo[i].lock_data_philo = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].lock_data_philo, NULL);
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
	while (++i < data->num_philo)
		pthread_join(philos[i].thread, NULL);
	monitoring(data, philos);
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
		pthread_mutex_destroy(philos[i].lock_data_philo);
		free(philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(data->pancil);
	free(data->pancil);
	free(philos);
	return (0);
}
