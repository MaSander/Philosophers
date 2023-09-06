/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:36:39 by msander-          #+#    #+#             */
/*   Updated: 2023/08/17 20:41:24 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_last_food(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_food_data);
	philo->last_food = get_time_now();
	pthread_mutex_unlock(philo->lock_food_data);
}

long	get_last_food(t_philo *philo)
{
	long	food;

	pthread_mutex_lock(philo->lock_food_data);
	food = philo->last_food;
	pthread_mutex_unlock(philo->lock_food_data);
	return (food);
}

void	increment_satisfied(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_satisfy_data);
	philo->satisfied++;
	pthread_mutex_unlock(philo->lock_satisfy_data);
}

int	get_satisfied(t_philo *philo)
{
	int	last_satisfied;

	pthread_mutex_lock(philo->lock_satisfy_data);
	last_satisfied = philo->satisfied;
	pthread_mutex_unlock(philo->lock_satisfy_data);
	return (last_satisfied);
}
