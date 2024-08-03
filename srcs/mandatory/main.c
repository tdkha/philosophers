/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:45:26 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/03 18:16:09 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	main(int ac, char **av)
{
	t_program	prog;

	memset(&prog, 0, sizeof(t_program));
	if ((ac != 5 && ac != 6) || !ft_arg_check(ac, av))
	{
		error_msg("Invalid argument(s)\n", &prog.mt_lock);
		exit(1);
	}
	if (ft_init(ac, av, &prog) == 0)
	{
		ft_free(&prog);
		exit(1);
	}
	if (simulation(&prog) == 0)
	{
		ft_free(&prog);
		exit(1);
	}
	// int i = 0;
	// while (i < prog.philo_count)
	// {
	// 	printf("Philo %d: %d\n", i + 1, prog.philos[i]->meal_eaten);
	// 	i++;
	// }
	ft_free(&prog);
	return (0);
}
