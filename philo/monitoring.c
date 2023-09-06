/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:24:02 by msander-          #+#    #+#             */
/*   Updated: 2023/08/21 20:39:24 by msander-         ###   ########.fr       */
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

int	philos_are_dissatisfied(t_philo *philos)
{
	int	i;
	int	philos_satisfied;

	i = -1;
	philos_satisfied = 0;
	while (++i < philos->data->num_philo)
	{
		if (get_satisfied(&philos[i]) == philos->data->num_philo_must_eat)
			philos_satisfied++;
	}
	return (philos->data->num_philo - philos_satisfied);
}

void	*monitoring(void *philo_array)
{
	int		i;
	t_data	*data;
	t_philo	*philos;

	philos = (t_philo *)philo_array;
	data = philos->data;
	while (philos_are_dissatisfied(philos))
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (get_satisfied(&philos[i]) != data->num_philo_must_eat)
				if (!philo_is_alive(&philos[i]))
					return (0);
			i++;
		}
		ft_sleep(1);
	}
	return (0);
}
