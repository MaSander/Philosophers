/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:28 by msander-          #+#    #+#             */
/*   Updated: 2023/09/06 23:33:10 by msander-         ###   ########.fr       */
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
		philo[i].left_fork = ft_calloc(sizeof(pthread_mutex_t), 1);
		philo[i].lock_food_data = ft_calloc(sizeof(pthread_mutex_t), 1);
		philo[i].lock_satisfy_data = ft_calloc(sizeof(pthread_mutex_t), 1);
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].lock_food_data, NULL);
		pthread_mutex_init(philo[i].lock_satisfy_data, NULL);
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
	int			i;
	pthread_t	monotoring_th;

	i = -1;
	data->life_start_time = get_time_now();
	while (++i < data->num_philo)
		pthread_create(&philos[i].thread, NULL, &life, &philos[i]);
	i = -1;
	ft_sleep(data->num_philo);
	pthread_create(&monotoring_th, NULL, &monitoring, philos);
	while (++i < data->num_philo)
		pthread_join(philos[i].thread, NULL);
	pthread_join(monotoring_th, NULL);
	return (0);
}

int	philosopher(t_data	*data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = ft_calloc(sizeof(t_philo), data->num_philo);
	if (!philos)
		return (-1);
	init_philo(data, philos);
	give_life(data, philos);
	ft_sleep(5);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(philos[i].left_fork);
		pthread_mutex_destroy(philos[i].lock_food_data);
		pthread_mutex_destroy(philos[i].lock_satisfy_data);
		free(philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(data->pancil);
	free(data->pancil);
	free(philos);
	return (0);
}
