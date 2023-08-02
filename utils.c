/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:54:12 by msander-          #+#    #+#             */
/*   Updated: 2023/08/02 15:31:39 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isalldigit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (*str);
		str++;
	}
	return (0);
}

int	ft_isdigit(char str)
{
	if (str > 47 && str < 58)
		return (2048);
	str++;
	return (0);
}

int	ft_atoi(const char *str)
{
	int	s;
	int	number;
	int	signal;

	signal = 1;
	number = 0;
	s = 0;
	while ((str[s] >= 9 && str[s] <= 13) || str[s] == 32)
		s++;
	if (str[s] == '-' || str[s] == '+')
		s++;
	while (ft_isdigit(str[s]))
	{
		if (str[s - 1] == '-')
			signal = -1;
		number = (number * 10) + (str[s] - 48);
		s++;
	}
	return (number * signal);
}

void	check_args(int argv, char *argc[])
{
	if (argv < 5)
		exit_error(1, "argument is missing");
	if (argv > 6)
		exit_error(1, "Too many arguments");
	if (ft_isalldigit(argc[1]) != 0)
		exit_error(2, "Invalid number of philosophers argument");
	if (ft_isalldigit(argc[2]) != 0)
		exit_error(2, "Invalid time to die argument");
	if (ft_isalldigit(argc[3]) != 0)
		exit_error(2, "Invalid time to eat argument");
	if (ft_isalldigit(argc[4]) != 0)
		exit_error(2, "Invalid time to sleep argument");
	if (argv == 6)
		if (ft_isalldigit(argc[5]) != 0)
			exit_error(2, "Invalid times each philosopher must eat argument");
}
