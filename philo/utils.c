/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:54:12 by msander-          #+#    #+#             */
/*   Updated: 2023/08/07 11:48:04 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;
	size_t	size_alloc;

	size_alloc = num * size;
	if (((size_alloc / size) != num) || ((size_alloc / num) != size))
		return (NULL);
	ptr = malloc(num * size);
	if (!ptr)
		return (NULL);
	size = 0;
	num = num * size;
	while (num--)
	{
		((unsigned char *)ptr)[size] = 0;
		size++;
	}
	return (ptr);
}

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
