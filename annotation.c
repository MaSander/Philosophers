/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annotation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:46:41 by msander-          #+#    #+#             */
/*   Updated: 2023/08/07 11:45:51 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_philo_action(t_philo *philo, int action)
{
	long	moment;

	pthread_mutex_lock(philo->data->pancil);
	if (philo->data->did_someone_die == 1)
	{
		pthread_mutex_unlock(philo->data->pancil);
		return ;
	}
	moment = calculate_current_time(philo);
	if (action == TAKE_A_FORK)
		printf("%ld %d has take a fork\n", moment, philo->name);
	else if (action == EATING)
		printf("%ld %d is eating\n", moment, philo->name);
	else if (action == SLEEPING)
		printf("%ld %d is sleeping\n", moment, philo->name);
	else if (action == THINKING)
		printf("%ld %d is thinking\n", moment, philo->name);
	else
		printf("%ld %d died\n", moment, philo->name);
	pthread_mutex_unlock(philo->data->pancil);
}
