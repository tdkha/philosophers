/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:45:26 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/29 01:25:16 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"


int	main(int ac, char **av)
{
	t_program	prog;

	memset(&prog, 0, sizeof(t_program));
	if ((ac != 5 && ac != 6) || !ft_arg_check(ac, av))
	{
		error_msg(&prog, "Invalid argument(s)\n");
		exit(1);
	}
	if (ft_init(ac, av, &prog) == 0)
	{
		printf("Failed to init\n");
		ft_free(&prog);
		exit(1);
	}
	printf("----------------------\n");
	printf("Program info:\n");
	printf("AC: %d\n", ac);
	printf("Philo count: %d\n", prog.philo_count);
	printf("----------------------\n");
	if (philosopher(&prog) == 0)
	{
		printf("Failed to run philosopher\n");
		ft_free(&prog);
		exit(1);
	}
	ft_free(&prog);
	return (0);
}
