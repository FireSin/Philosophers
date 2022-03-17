/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:40:11 by rrast             #+#    #+#             */
/*   Updated: 2022/03/16 14:07:59 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_unlink(void)
{
	sem_unlink("/die");
	sem_unlink("/forks");
	sem_unlink("/all_eat");
	sem_unlink("/print");
	sem_unlink("/timeph");
}

void	freedata(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (data->philo)
	{
		kill(data->philo->pid, SIGKILL);
		tmp = data->philo->next;
		free(data->philo);
		data->philo = tmp;
	}
	sem_close(data->vars.timeph);
	sem_close(data->vars.die);
	sem_close(data->vars.forks);
	if (data->vars.numeat > 0)
		sem_close(data->vars.ate);
	sem_close(data->vars.print);
	ft_unlink();
}
