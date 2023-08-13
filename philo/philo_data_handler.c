/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:36:39 by msander-          #+#    #+#             */
/*   Updated: 2023/08/13 02:39:15 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_last_food(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_data_philo);
	philo->last_food = get_time_now();
	pthread_mutex_unlock(philo->lock_data_philo);
}

long	get_last_food(t_philo *philo)
{
	long	food;

	pthread_mutex_lock(philo->lock_data_philo);
	food = philo->last_food;
	pthread_mutex_unlock(philo->lock_data_philo);
	return (food);
}

void	increment_satisfied(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_data_philo);
	philo->satisfied++;
	pthread_mutex_unlock(philo->lock_data_philo);
}

int	get_satisfied(t_philo *philo)
{
	int	last_satisfied;

	pthread_mutex_lock(philo->lock_data_philo);
	last_satisfied = philo->satisfied;
	pthread_mutex_unlock(philo->lock_data_philo);
	return (last_satisfied);
}
