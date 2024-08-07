/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:17:18 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/07 13:30:50 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	non_blocking_error_msg(char *str)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
}

int	non_blocking_error_msg_ret(char *str, int val)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	return (val);
}

void	error_msg(char *str, sem_t *sem_shared)
{
	int	len;

	if (sem_wait(sem_shared) != 0)
	{
		non_blocking_error_msg("Error in error_msg from sem_wait()\n");
	}
	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	if (sem_post(sem_shared) != 0)
	{
		non_blocking_error_msg("Error in error_msg from sem_wait()\n");
	}
}

int	error_msg_ret(char *str, sem_t *sem_shared, int return_val)
{
	int	len;

	if (sem_wait(sem_shared) != 0)
	{
		non_blocking_error_msg("Error in error_msg from sem_wait()\n");
		return (0);
	}
	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	if (sem_post(sem_shared) != 0)
	{
		non_blocking_error_msg("Error in error_msg from sem_wait()\n");
		return (0);
	}
	return (return_val);
}

int	philo_msg(t_philo *philo, char *str)
{
	size_t	time;

	time = get_current_time() - philo->start_ms;
	if (sem_wait(philo->prog->sem_shared) != 0)
	{
		non_blocking_error_msg("Error in philo_msg from sem_wait()\n");
		return (0);
	}
	printf("%zu %d %s\n", time, philo->id + 1, str);
	if (sem_post(philo->prog->sem_shared) != 0)
	{
		non_blocking_error_msg("Error in philo_msg from sem_post()\n");
		return (0);
	}
	return (1);
}
