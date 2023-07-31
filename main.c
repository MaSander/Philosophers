/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:47:28 by msander-          #+#    #+#             */
/*   Updated: 2023/07/30 23:48:13 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_args(t_data *data, int argc, char *argv[])
{
    data->num_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->num_philo_must_eat = ft_atoi(argv[5]);
}

void *philo_life(void *arg)
{
    t_data *data = (t_data *)arg;
    printf("philo has take a fork\n");
    
    printf("philo is eating\n");
    usleep(data->time_to_eat * 1000);
    printf("-data->time_to_eat: %d-\n", data->time_to_eat);
    
    printf("philo is sleeping\n");
    usleep(data->time_to_sleep * 1000);
    printf("-data->time_to_sleep: %d-\n", data->time_to_sleep);
    
    printf("philo is thinking\n");
    usleep(data->time_to_die * 1000);
    printf("-data->time_to_die: %d-\n", data->time_to_die);
    
    printf("philo died\n");

    return (0);
}

int main(int argc, char *argv[])
{
    t_data data;
    t_philo *philo;

    check_args(argc, argv);
    init_args(&data, argc, argv);
    
    printf("data: %d, %d, %d\n\n", data.time_to_eat, data.time_to_sleep, data.time_to_die);
    // philo = (struct t_philo *)malloc(sizeof(t_philo));
    philo = malloc(sizeof(t_philo));

    // philo->thread = (struct pthread_t *)malloc(sizeof(pthread_t));

    pthread_create(&philo->thread, NULL, &philo_life, &data);

    pthread_join(philo->thread, NULL);
    // init_data();
    /* TODO
        verificar argumentos
        salvar argumentos
        criar os philos
    */
    return (0);
}