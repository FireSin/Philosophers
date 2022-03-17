/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:17:46 by rrast             #+#    #+#             */
/*   Updated: 2022/02/24 15:49:12 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	takearg(argc, argv, &data.vars);
	if (data.vars.nphilo < 0)
		return (1);
	if (initphilo(&data))
	{
		printf("Error init\n");
		return (1);
	}
	threads(&data);
	ft_usleep(data.vars.teat);
	freedata(&data);
	return (0);
}
