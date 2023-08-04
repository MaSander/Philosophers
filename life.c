/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:01 by msander-          #+#    #+#             */
/*   Updated: 2023/08/03 21:53:23 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	write_philo_action(philo, TAKE_A_FORK);
	write_philo_action(philo, TAKE_A_FORK);
	write_philo_action(philo, EATING);
	philo->last_food = get_time_now();
	philo->satisfied++;
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	write_philo_action(philo, SLEEPING);
	ft_sleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	write_philo_action(philo, THINKING);
}

void	*life(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (!(ph->name % 2))
		ft_sleep(1);
	ph->last_food = ph->data->life_start_time;
	while (ph->data->did_someone_die != 1)
	{
		if (ph->data->num_philo_must_eat == ph->satisfied)
			return (0);
		eating(ph);
		sleeping(ph);
		thinking(ph);
	}
	return (0);
}
