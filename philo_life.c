/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:01 by msander-          #+#    #+#             */
/*   Updated: 2023/08/02 15:33:40 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*sleeping(void *philo);
void	*thinking(void *philo);

void	*live_alone(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	printf("%d has take a fork\n", ph->name);
	printf("%d is eating\n", ph->name);
	printf("%d is sleeping\n", ph->name);
	printf("%d is thinking\n", ph->name);
	return (0);
}

void	*eating(void *philo)
{
	t_philo	*ph;
	long	moment;

	ph = (t_philo *)philo;
	if (ph->data->num_philo_must_eat == ph->satisfied)
		return (0);
	ph->satisfied++;
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	moment = calculate_philo_moment(philo);
	printf("%ld %d has take a fork\n", moment, ph->name);
	printf("%ld %d is eating\n", moment, ph->name);
	usleep(ph->data->time_to_eat * 1000);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	return (sleeping(philo));
}

void	*sleeping(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	printf("%ld %d is sleeping\n", calculate_philo_moment(philo), ph->name);
	usleep(ph->data->time_to_sleep * 1000);
	return (thinking(philo));
}

void	*thinking(void *philo)
{
	long	moment;

	moment = calculate_philo_moment(philo);
	printf("%ld %d is thinking\n", moment, ((t_philo *)philo)->name);
	return (eating(philo));
}

int	philo_life(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->life_start_time = get_time_now();
	if (data->num_philo == 1)
	{
		pthread_create(&philo->thread, NULL, &live_alone, &philo);
		pthread_join(philo->thread, NULL);
	}
	else
	{
		while (i < data->num_philo)
		{
			pthread_create(&philo[i].thread, NULL, &eating, &philo[i]);
			i++;
		}
		while (i < data->num_philo)
		{
			pthread_join(philo[i].thread, NULL);
		}
	}
	return (i);
}
