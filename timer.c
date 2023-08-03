/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:52:11 by msander-          #+#    #+#             */
/*   Updated: 2023/08/03 11:52:14 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(int miliseconds)
{
	long	start_time;

	start_time = get_time_now();
	while ((get_time_now() - start_time) < (long)miliseconds)
		usleep(10);
}

long	calculate_current_time(t_philo *philo)
{
	return (get_time_now() - philo->data->life_start_time);
}
