/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:29:55 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/24 10:33:58 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_mutex(t_mutex *mutex, t_mutex_code code, t_program *prog)
{
	int	error;

	error = 0;
	if (code == INIT)
		error = pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		error = pthread_mutex_destroy(mutex);
	else if (code == LOCK)
		error = pthread_mutex_lock(mutex)	;
	else if (code == UNLOCK)
		error = pthread_mutex_unlock(mutex);
	else
		return (0);
	if (error != 0)
	{
		if (code == INIT)
			error_msg(prog, "Error occured when calling <pthread_mutex_init>\n");
		else if (code == DESTROY)
			error_msg(prog, "Error occured when calling <pthread_mutex_destroy>\n");
		else if (code == LOCK)
			error_msg(prog, "Error occured when calling <pthread_mutex_lock>\n");
		else if (code == UNLOCK)
			error_msg(prog, "Error occured when calling <pthread_mutex_unlock>\n");
	}
	return (1);
}
