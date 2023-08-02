/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:52:11 by msander-          #+#    #+#             */
/*   Updated: 2023/08/02 01:33:52 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosophers.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/time.h>
#include <time.h>

long get_time_now(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main(int argv, char *argc)
{
	struct timeval	tv;
	long			time_now;
	long			first_time_now;

	first_time_now = get_time_now();
	while (1)
	{
		gettimeofday(&tv, NULL);
		time_now = get_time_now();
		usleep(100000);
		printf("%ld\n", time_now - first_time_now);
	}
	return (0);
}