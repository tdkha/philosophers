/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:45:26 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/22 18:55:50 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"


int	main(int ac, char **av)
{
	t_program	prog;

	memset(&prog, 0, sizeof(t_program));
	if (ft_init(ac, av, &prog) == 0)
		exit(1);
	//philosopher(&prog);
	ft_free(&prog);
	if (prog.error)
		exit(1);
	return (0);
}
