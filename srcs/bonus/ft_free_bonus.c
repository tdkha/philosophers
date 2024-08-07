/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:47 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/07 14:28:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static int	ft_sem_unlink(t_program *prog)
{
	int	status;

	status = sem_unlink("forks");
	if (status != 0)
		return (0);
	status = sem_unlink("shared");
	if (status != 0)
		return (0);
	status = sem_unlink("activate");
	if (status != 0)
		return (0);
	status = sem_unlink("end");
	if (status != 0)
		return (0);
	return (1);
}

static int	ft_sem_destroy(t_program *prog)
{
	int	status;

	status = sem_close(prog->sem_forks);
	if (status != 0)
	{
		return (0);
	}
	status = sem_close(prog->sem_shared);
	if (status != 0)
		return (0);
	status = sem_close(prog->sem_activate);
	if (status != 0)
		return (0);
	status = sem_close(prog->sem_end);
	if (status != 0)
		return (0);
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

int	ft_free(t_program *prog)
{
	if (ft_sem_destroy(prog) == 0)
		return (non_blocking_error_msg_ret("Error in ft_sem_destroy from sem_close()\n", 0));
	if (ft_sem_unlink(prog) == 0)
		return (non_blocking_error_msg_ret("Error in ft_sem_unlink from sem_unlink()\n", 0));
	ft_philos_clean(prog);
	free(prog);
	return (1);
}
