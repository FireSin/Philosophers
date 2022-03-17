/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:40:11 by rrast             #+#    #+#             */
/*   Updated: 2022/02/24 15:42:31 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	freedata(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (data->philo)
	{
		pthread_mutex_destroy(&data->philo->tmute);
		tmp = data->philo->next;
		free(data->philo);
		data->philo = tmp;
	}
	while (i < data->vars.nphilo)
		pthread_mutex_destroy(&data->forks[i++]);
	free (data->forks);
	pthread_mutex_destroy(&data->vars.lockdie);
	pthread_mutex_destroy(&data->vars.mutex);
}
