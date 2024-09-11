/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:16:37 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/11 17:25:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/**
 * Function to malloc and init the propertis of <t_philo> type
 * Description:
 * - The id starts at 0
 * 
 */
static int	ft_philos_init(t_program *prog)
{
	int		i;
	size_t	start_ms;

	i = -1;
	start_ms = get_current_time() + 3000;
	while (++i < prog->philo_count)
	{
		prog->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!prog->philos[i])
			return (error_msg_ret("ft_philos_init: malloc\n", 0));
		memset(prog->philos[i], 0, sizeof(t_philo));
		prog->philos[i]->id = i;
		prog->philos[i]->start_ms = start_ms;
		prog->philos[i]->last_meal_ms = start_ms;
		prog->philos[i]->prog = prog;
		if (!ft_make_sem(prog->philos[i], i))
			return (0);
	}
	return (1);
}

/**
 * Function to init all the semaphores
 * <1> sem_shared
 * <2> sem_forks
 * <3> sem_activate
 * 
 * Description: 
 * - sem_shared counter is set to 1
 * - sem_forks counter is equal to a number of forks (or philosophers)
 * - sem_activate counter is equal to a half of philosophers (odd or even scheme)
 */
static int	ft_sem_init(t_program *prog)
{
	sem_unlink("philo_print");
	prog->sem_print = sem_open("philo_print", O_CREAT, 0644, 1);
	if (prog->sem_print == SEM_FAILED)
		return (0);
	sem_unlink("philo_forks");
	prog->sem_forks = sem_open("philo_forks", O_CREAT, 0644, prog->philo_count);
	if (prog->sem_forks == SEM_FAILED)
		return (0);
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
	if (ac == 6)
		prog->must_eat = ft_atold(av[5]);
	else
		prog->must_eat = -1;
	prog->philos = (t_philo **)
		ft_calloc((prog->philo_count + 1), sizeof(t_philo *));
	if (!prog->philos)
		return (0);
	if (!ft_philos_init(prog))
		return (0);
	if (!ft_sem_init(prog))
	{
		ft_philos_clean(prog);
		return (0);
	}
	return (1);
}
