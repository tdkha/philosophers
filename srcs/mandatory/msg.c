/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/28 23:47:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	error_msg(t_program *prog, char *str)
{
	int	len;

	ft_mutex(&prog->mt_lock_print, LOCK, prog);
	len = (int) ft_strlen(str);
	ft_mutex(&prog->mt_lock_print, UNLOCK, prog);
	write(2, str, len);
}

int	error_msg_ret(t_program *prog, char *str, int return_val)
{
	int	len;

	ft_mutex(&prog->mt_lock_print, LOCK, prog);
	len = (int) ft_strlen(str);
	write(2, str, len);
	ft_mutex(&prog->mt_lock_print, UNLOCK, prog);
	return (return_val);
}

void	philo_msg(t_philo *philo, t_philo_status status)
{
	ft_mutex(&philo->prog->mt_lock_print, LOCK, philo->prog);
	if (status == FORK_UP_L || status == FORK_UP_R)
		printf("%d has taken a fork\n", philo->id);
	else if (status == EAT)
		printf("%d is eating\n", philo->id);
	else if (status == THINK)
		printf("%d is thinking\n", philo->id);
	else if (status == SLEEP)
		printf("%d is sleeping\n", philo->id);
	else if (status == DIE)
		printf("%d died\n", philo->id);
	ft_mutex(&philo->prog->mt_lock_print, UNLOCK, philo->prog);
}
