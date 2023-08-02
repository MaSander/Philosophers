/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:01 by msander-          #+#    #+#             */
/*   Updated: 2023/08/02 19:39:34 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	eating(t_philo *philo)
{
	long	moment;

	if (philo->data->num_philo_must_eat == philo->satisfied)
		return ;
	philo->satisfied++;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	moment = calculate_philo_moment(philo);
	printf("%ld %d has take a fork\n", moment, philo->name);
	printf("%ld %d is eating\n", moment, philo->name);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", calculate_philo_moment(philo), philo->name);
	usleep(philo->data->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	long	moment;

	moment = calculate_philo_moment(philo);
	printf("%ld %d is thinking\n", moment, philo->name);
}

void	*life(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (!(ph->name % 2))
		usleep(1000);
	while (1 == 1)
	{
		eating(ph);
		sleeping(ph);
		thinking(ph);
	}
	return (0);
}

int	philo_life(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	data->life_start_time = get_time_now();
	if (data->num_philo == 1)
	{
		pthread_create(&philo->thread, NULL, &live_alone, &philo);
		pthread_join(philo->thread, NULL);
	}
	else
	{
		while (++i < data->num_philo)
			pthread_create(&philo[i].thread, NULL, &life, &philo[i]);
		i = -1;
		while (++i < data->num_philo)
			pthread_join(philo[i].thread, NULL);
	}
	return (i);
}
