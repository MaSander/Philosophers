/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander- <msander-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:10:13 by msander-          #+#    #+#             */
/*   Updated: 2023/07/30 18:28:57 by msander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void exit_error(int exit_code, char *message_error)
{
	//TODO: perror(message_error);
	printf("Error: %s\n", message_error);
	exit(exit_code);
}
