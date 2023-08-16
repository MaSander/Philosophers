/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:24:02 by msander-          #+#    #+#             */
/*   Updated: 2023/08/15 21:43:46 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_alive(t_philo *philo)
{
	long	time_now;
	long	last_food;

	time_now = get_time_now();
	last_food = get_last_food(philo);
	if (last_food != 0)
	{
		if ((time_now - last_food) > philo->data->time_to_die)
		{
			write_philo_action(philo, DIED);
			register_death(philo->data);
			return (0);
		}
	}
	return (1);
}

void	monitoring(t_data *data, t_philo *philos)
{
	int	i;
	int	philos_satisfied;

	ft_sleep(2);
	philos_satisfied = 0;
	while (philos_satisfied != data->num_philo)
	{
		i = 0;
		philos_satisfied = 0;
		while (i < data->num_philo)
		{
			if (get_satisfied(&philos[i]) != data->num_philo_must_eat)
				if (!philo_is_alive(&philos[i]))
					return ;
			i++;
		}
		i = 0;
		while (i < data->num_philo)
		{
			if (get_satisfied(&philos[i]) == data->num_philo_must_eat)
				philos_satisfied++;
			i++;
		}
	}
}
