/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:28:23 by rrast             #+#    #+#             */
/*   Updated: 2022/03/16 14:30:02 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	check_arg(char *str)
{
	unsigned int	dig;

	dig = 0;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
		{
			printf("Error arguments\n");
			return (-1);
		}
		dig = 10 * (dig) + (*str++ - '0');
	}
	if (dig > 2147483647)
	{
		printf("Error arguments\n");
		return (-1);
	}
	return (dig);
}

void	takearg(int argc, char **argv, t_vars *vars)
{
	vars->numeat = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Incorrect number arguments\n");
		vars->nphilo = -1;
		return ;
	}
	vars->nphilo = check_arg(argv[1]);
	vars->tdie = check_arg(argv[2]);
	vars->teat = check_arg(argv[3]);
	vars->tsleep = check_arg(argv[4]);
	if (argc == 6)
		vars->numeat = check_arg(argv[5]);
	else
		vars->numeat = -2;
	if (vars->nphilo < 0 || vars->tdie < 0 \
		|| vars->teat < 0 || vars->tsleep < 0 \
		|| vars->numeat == -1)
		vars->nphilo = -1;
}
