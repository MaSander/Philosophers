/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:01 by msander-          #+#    #+#             */
/*   Updated: 2023/08/01 14:42:10 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*sleeping(void *philo);
void	*thinking(void *philo);

void	*live_alone()
{
	printf("test\n");
	return (0);
}

void	*eating(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	if (ph->data->num_philo_must_eat == ph->satisfied)
		return (0);
	ph->satisfied++;
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	printf("%d has take a fork\n", ph->name);
	printf("%d is eating\n", ph->name);
	usleep(ph->data->time_to_eat * 1000);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	return (sleeping(philo));
}

void	*sleeping(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	printf("%d is sleeping\n", ph->name);
	usleep(ph->data->time_to_sleep * 1000);
	return (thinking(philo));
}

void	*thinking(void *philo)
{
	printf("%d is thinking\n", ((t_philo *)philo)->name);
	return (eating(philo));
}

int	philo_life(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		if (philo[i].name % 2)
			pthread_create(&philo[i].thread, NULL, &eating, &philo[i]);
		else
			pthread_create(&philo[i].thread, NULL, &sleeping, &philo[i]);
		i++;
	}
	while (i < data->num_philo)
	{
		printf("join...\n");
		pthread_join(philo[i].thread, NULL);
	}
	return (i);
}
