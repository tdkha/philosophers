/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:22:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/02 13:06:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

size_t	get_current_time(t_mutex *mt_lock_print)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg("Error occurred when calling <gettimeofday>\n", mt_lock_print);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_mutex *mt_lock_print)
{
	size_t	start;

	start = get_current_time(mt_lock_print);
	while ((get_current_time(mt_lock_print) - start) < milliseconds)
		usleep(500);
	return (0);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
