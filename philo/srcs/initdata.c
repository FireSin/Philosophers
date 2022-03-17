/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:11:30 by rrast             #+#    #+#             */
/*   Updated: 2022/02/22 16:51:52 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	takedata(t_data *data, t_philo *p, int i)
{
	p->left = &data->forks[i];
	p->right = &data->forks[++i];
	p->numph = i;
	p->vars = &data->vars;
	p->next = NULL;
	p->neat = data->vars.numeat;
	p->time = 0;
	return (i);
}

int	initphilostruct(t_data *data)
{
	t_philo	*p;
	t_philo	*temp;
	int		i;

	i = 0;
	while (i < data->vars.nphilo)
	{
		p = (t_philo *)malloc(sizeof(t_philo));
		if (!p)
			return (1);
		i = takedata(data, p, i);
		if (!(data->philo))
			data->philo = p;
		else
			temp->next = p;
		temp = p;
		p = NULL;
	}
	temp->right = &data->forks[0];
	return (0);
}

int	initphilo(t_data *data)
{
	int	i;

	i = 0;
	data->forks = NULL;
	data->philo = NULL;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->vars.nphilo);
	if (!data->forks)
		return (1);
	while (i < data->vars.nphilo)
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (1);
	if (initphilostruct(data))
		return (1);
	return (0);
}
