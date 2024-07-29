/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:47 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/29 01:03:15 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_free(t_program *prog)
{
	printf("Free called\n");
	ft_mutexes_clean(prog);
	ft_philos_clean(prog);
	free(prog->activated);
	return (1);
}
