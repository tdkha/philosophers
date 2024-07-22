/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:08:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/22 23:30:28 by ktieu            ###   ########.fr       */
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
			return (error_msg_ret("Failed to malloc type (t_philo *)\n", 0));
		}
        memset(prog->philos[i], 0, sizeof(t_philo));
        prog->philos[i]->id = i;
        prog->philos[i]->prog = prog;
		i++;
	}
	return (1);
}

static int	ft_mutexes_init(t_program *prog)
{
	int	i;

	i = 0;
	if (!ft_mutex(&prog->mt_lock_meal, INIT))
		return (0);
	if (!ft_mutex(&prog->mt_lock_print, INIT))
	{
		ft_mutex(&prog->mt_lock_meal, DESTROY);
		return (0);
	}
	while (i < prog->philo_count)
	{
		if (!ft_mutex(&prog->mt_forks[i], INIT))
		{
			ft_clean(prog, MUTEX);
			return (error_msg_ret("Failed to init type (t_mutex *)", 0));
		}
		++i;
	}
	return (1);
}

int	ft_init(int ac, char **av, t_program *prog)
{
	prog->ac = ac;
	prog->av = av;
	prog->error = 0;
	if (ac != 5 || !ft_arg_check(ac, av))
		return (error_msg_ret("Invalid argument(s)\n", 0));
	prog->philo_count = (int) ft_atold(av[1]);
	prog->time_die = ft_atold(av[2]);
	prog->time_eat = ft_atold(av[3]);
	prog->time_sleep = ft_atold(av[4]);
	prog->philos = (t_philo **)
		ft_calloc((prog->philo_count + 1), sizeof(t_philo *));
	if (!prog->philos)
		return (error_msg_ret("Failed to malloc type (t_philo **)\n", 0));
	prog->mt_forks = (t_mutex *)
		ft_calloc(prog->philo_count, sizeof(t_mutex));
	if (!prog->mt_forks)
		return (error_msg_ret("Failed to malloc type (t_mutex **)\n", 0));
	if (!ft_philos_init(prog) || !ft_mutexes_init(prog))
	{
		ft_free(prog);
		return (0);
	}
	return (1);
}
