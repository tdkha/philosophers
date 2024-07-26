/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:08:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/26 07:40:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	ft_philos_init(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		prog->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!prog->philos[i])
		{
			ft_clean(prog, PHILO);
			return (error_msg_ret(prog, "Failed to malloc type (t_philo *)\n", 0));
		}
        memset(prog->philos[i], 0, sizeof(t_philo));
        prog->philos[i]->id = i + 1;
        prog->philos[i]->prog = prog;
		i++;
	}
	return (1);
}

/**
 * Function to init all the mutexes in the program
 * List of mutexes:
 * <1> mt_lock_meal
 * <2> mt_lock_print
 * <3> mt_forks (array of mutexes)
 */
static int	ft_mutexes_init(t_program *prog)
{
	int	i;

	i = 0;
	if (!ft_mutex(&prog->mt_lock_meal, INIT, prog))
		return (0);
	if (!ft_mutex(&prog->mt_lock_print, INIT, prog))
	{
		ft_mutex(&prog->mt_lock_meal, DESTROY, prog);
		return (0);
	}
	while (i < prog->philo_count)
	{
		if (!ft_mutex(&prog->mt_forks[i], INIT, prog))
		{
			ft_clean(prog, MUTEX);
			return (error_msg_ret(prog, "Failed to init type (t_mutex *)", 0));
		}
		++i;
	}
	return (1);
}

int	ft_init(int ac, char **av, t_program *prog)
{
	prog->ac = ac;
	prog->av = av;
	prog->philo_count = (int) ft_atold(av[1]);
	prog->time_die = ft_atold(av[2]);
	prog->time_eat = ft_atold(av[3]);
	prog->time_sleep = ft_atold(av[4]);
	prog->philos = (t_philo **)
		ft_calloc((prog->philo_count + 1), sizeof(t_philo *));
	if (!prog->philos)
		return (error_msg_ret(prog, "Failed to malloc type (t_philo **)\n", 0));
	prog->activated = (int *) ft_calloc((prog->philo_count), sizeof(int));
	if (!prog->activated)
		return (error_msg_ret(prog, "Failed to malloc type (int *)\n", 0));
	prog->mt_forks = (t_mutex *)
		ft_calloc(prog->philo_count, sizeof(t_mutex));
	if (!prog->mt_forks)
		return (error_msg_ret(prog, "Failed to malloc type (t_mutex **)\n", 0));
	if (!ft_philos_init(prog) || !ft_mutexes_init(prog))
	{
		return (0);
	}
	return (1);
}
