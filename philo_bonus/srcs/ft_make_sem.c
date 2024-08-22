/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_sem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:20:26 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/22 17:38:24 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_make_prefix(char *sem_name, int i, char *prefix)
{
	int	j;

	j = 0;
	while (prefix[j])
	{
		sem_name[i++] = prefix[j];
		++j;
	}
	return (i);
}

static void	ft_make_sem_ter(t_philo *philo, int id, int i, int j)
{
	int		len;
	char	temp;

	len = 0;
	i = ft_make_prefix(philo->sem_ter_name, i, "term");
	if (id == 0)
	{
		philo->sem_ter_name[i++] = '0';
		philo->sem_ter_name[i] = '\0';
		return ;
	}
	while (id > 0)
	{
		philo->sem_ter_name[i + len] = (id % 10) + '0';
		id /= 10;
		++len;
	}
	while (j < len / 2)
	{
		temp = philo->sem_ter_name[i + j];
		philo->sem_ter_name[i + j] = philo->sem_ter_name[i + len - 1 - j];
		philo->sem_ter_name[i + len - 1 - j] = temp;
		j++;
	}
	philo->sem_ter_name[i + len] = '\0';
}

static void	ft_make_sem_shared(t_philo *philo, int id, int i, int j)
{
	int		len;
	char	temp;

	len = 0;
	i = ft_make_prefix(philo->sem_shared_name, i, "share");
	if (id == 0)
	{
		philo->sem_shared_name[i++] = '0';
		philo->sem_shared_name[i] = '\0';
		return ;
	}
	while (id > 0)
	{
		philo->sem_shared_name[i + len] = (id % 10) + '0';
		id /= 10;
		++len;
	}
	while (j < len / 2)
	{
		temp = philo->sem_shared_name[i + j];
		philo->sem_shared_name[i + j] = philo->sem_shared_name[i + len - 1 - j];
		philo->sem_shared_name[i + len - 1 - j] = temp;
		j++;
	}
	philo->sem_shared_name[i + len] = '\0';
}

int	ft_make_sem(t_philo *philo, int i)
{
	ft_make_sem_ter(philo, i, 0, 0);
	ft_make_sem_shared(philo, i, 0, 0);
	sem_unlink(philo->sem_ter_name);
	sem_unlink(philo->sem_shared_name);
	philo->sem_terminate = sem_open(philo->sem_ter_name, O_CREAT, 0644, 1);
	if (philo->sem_terminate == SEM_FAILED)
		return (error_msg_ret("ft_make_sem: sem_open(): terminate\n", 0));
	philo->sem_shared = sem_open(philo->sem_shared_name, O_CREAT, 0644, 1);
	if (philo->sem_shared == SEM_FAILED)
		return (error_msg_ret("ft_make_sem: sem_open(): shared\n", 0));
	return (1);
}
