/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:01 by msander-          #+#    #+#             */
/*   Updated: 2023/08/03 19:09:32 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_is_alive(t_philo *philo)
{
	if ((get_time_now() - philo->last_food) > philo->data->time_to_die
		&& philo->last_food != 0)
	{
		write_philo_action(philo, DIED);
		philo->data->did_someone_die = 1;
		return (0);
	}
	return (1);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (philo->data->num_philo > 1)
		pthread_mutex_lock(&philo->right_fork);
	write_philo_action(philo, TAKE_A_FORK);
	write_philo_action(philo, EATING);
	philo->satisfied++;
	philo->last_food = get_time_now();
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	if (philo->data->num_philo > 1)
		pthread_mutex_unlock(&philo->right_fork);
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
		usleep(1000);
	while (ph->data->num_philo_must_eat != ph->satisfied)
	{
		if (!philo_is_alive(ph))
			return (0);
		eating(ph);
		if (!philo_is_alive(ph))
			return (0);
		sleeping(ph);
		if (!philo_is_alive(ph))
			return (0);
		thinking(ph);
	}
	return (0);
}
