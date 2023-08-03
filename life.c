/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:01 by msander-          #+#    #+#             */
/*   Updated: 2023/08/03 02:50:39 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*live_alone(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	write_philo_action(ph, TAKE_A_FORK);
	write_philo_action(ph, EATING);
	write_philo_action(ph, SLEEPING);
	write_philo_action(ph, THINKING);
	return (0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	write_philo_action(philo, TAKE_A_FORK);
	write_philo_action(philo, EATING);
	philo->satisfied++;
	philo->last_food = get_time_now();
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	write_philo_action(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
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
		usleep(1000);
	while (ph->data->num_philo_must_eat != ph->satisfied)
	{
		if ((get_time_now() - ph->last_food) > ph->data->time_to_die && ph->last_food != 0)
		{
			write_philo_action(philo, DIED);
			ph->data->did_someone_die = 1;
			return (0);
		}
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
