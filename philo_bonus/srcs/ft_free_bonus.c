/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:47 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/19 17:57:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_sem_clean(t_program *prog)
{
	if (sem_close(prog->sem_forks))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_close\n", 0));
	if (sem_close(prog->sem_shared))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_close\n", 0));
	if (sem_close(prog->sem_activate))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_close\n", 0));
	if (sem_close(prog->sem_print))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_close\n", 0));
	if (sem_close(prog->sem_terminate))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_close\n", 0));
	if (sem_unlink("philo_forks"))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_unlink\n", 0));
	if (sem_unlink("philo_shared"))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_unlink\n", 0));
	if (sem_unlink("philo_activate"))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_unlink\n", 0));
	if (sem_unlink("philo_print"))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_unlink\n", 0));
	if (sem_unlink("philo_terminate"))
		return (error_msg_ret("philo_bonus: ft_sem_clean: sem_unlink\n", 0));
	return (1);
}

int	ft_philos_clean(t_program *prog)
{
	int	i;

	i = 0;
	if (prog->philos)
	{
		while (i < prog->philo_count)
		{
			if (!prog->philos[i])
				break ;
			free(prog->philos[i]);
			prog->philos[i] = NULL;
			i++;
		}
		free(prog->philos);
		prog->philos = NULL;
	}
	return (1);
}

/**
 * Description:
 * - sem_post in case the philosopher dies (lock until here)
 * - Do not handle the failure of sem function here
 */
int	ft_free(t_program *prog)
{
	ft_sem_clean(prog);
	ft_philos_clean(prog);
	free(prog);
	return (1);
}
