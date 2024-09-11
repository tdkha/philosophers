/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/11 17:21:13 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_msg(char *str)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
}

void	error_msg_exit(char *str, int exitcode)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	exit(exitcode);
}

int	error_msg_ret(char *str, int return_val)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	return (return_val);
}

/**
 * Function to print out an action of a philosopher
 * 
 * Description: 
 * 
 * - The function first checks for the death of a philosopher before
 * deciding to print or not.
 * - The return of this function should checked
 * 
 */
int	philo_msg(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->mt_print);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(philo->mt_print);
		return (1);
	}
	time = get_current_time() - philo->start_ms;
	printf("%zu %d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(philo->mt_print);
	return (1);
}
