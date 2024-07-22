/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:30:32 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/22 18:07:50 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_thread(
	t_thread *thread,
	void *(*func)(void *),
	void *arg,
	t_thead_code code)
{
	int	error;

	error = 0;
	if (code == CREATE)
		error = pthread_create(thread, NULL, func, arg);
	else if (code == JOIN)
		error = pthread_join(*thread, NULL);
	else
		return (0);
	if (error != 0)
	{
		if (code == CREATE)
		{
			error_msg("Error occured when calling <pthread_create>\n");
		}
		else if (code == JOIN)
		{
			error_msg("Error occured when calling <pthread_join>\n");
		}
		return (0);
	}
	return (1);
}
