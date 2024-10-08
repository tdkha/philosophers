/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:45:26 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/11 17:13:17 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_program	prog;

	memset(&prog, 0, sizeof(t_program));
	if ((ac != 5 && ac != 6) || !ft_arg_check(ac, av))
	{
		error_msg("Invalid argument(s)\n");
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
	ft_free(&prog);
	return (0);
}
