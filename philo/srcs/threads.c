/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:17:28 by rrast             #+#    #+#             */
/*   Updated: 2022/02/24 17:54:46 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cheackeat(t_philo *philo)
{
	if (philo->neat > 0)
		philo->neat--;
	if (philo->neat == 0)
	{
		pthread_mutex_lock(&philo->tmute);
		pthread_mutex_lock(&philo->vars->alleating);
		if (--philo->vars->alleat == 0)
			pthread_mutex_lock(&philo->vars->mutex);
		pthread_mutex_unlock(&philo->vars->alleating);
	}
}

void	*cheackdeathphilo(void *dat)
{
	t_philo		*tmp;
	long int	time;

	tmp = (t_philo *)dat;
	while (1)
	{
		pthread_mutex_lock(&tmp->tmute);
		time = taketime() - tmp->vars->timeprog - tmp->time;
		if (time >= tmp->vars->tdie)
		{
			pthread_mutex_lock(&tmp->vars->mutex);
			pthread_mutex_lock(&tmp->vars->lockdie);
			tmp->vars->die = 0;
			printf("%ld %d died\n", \
				taketime() - tmp->vars->timeprog, tmp->numph);
			pthread_mutex_unlock(&tmp->vars->lockdie);
			return (NULL);
		}
		pthread_mutex_unlock(&tmp->tmute);
		usleep(100);
	}
	return (NULL);
}

void	*philoact(void *dat)
{
	t_philo			*philo;

	philo = (t_philo *)dat;
	while (1)
	{
		if (philo->neat != 0)
		{
			pthread_mutex_lock(philo->left);
			ft_myprint("has taken a fork", philo);
			pthread_mutex_lock(philo->right);
			pthread_mutex_lock(&philo->tmute);
			philo->time = taketime() - philo->vars->timeprog;
			pthread_mutex_unlock(&philo->tmute);
			ft_myprint("is eating", philo);
			ft_usleep(philo->vars->teat);
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			cheackeat(philo);
			ft_myprint("is sleeping", philo);
			ft_usleep(philo->vars->tsleep);
			ft_myprint("is thinking", philo);
		}
	}
	return (NULL);
}

void	takethreads(t_data data, int i)
{
	t_philo	*p;

	if (i == 0)
		p = data.philo;
	else
		p = data.philo->next;
	while (i < data.vars.nphilo)
	{
		pthread_mutex_init(&p->tmute, NULL);
		pthread_create(&p->tid, NULL, philoact, (void *)p);
		pthread_create(&p->tideath, NULL, cheackdeathphilo, (void *)p);
		i += 2;
		if (i < data.vars.nphilo)
			p = p->next->next;
	}
}

void	threads(t_data *data)
{
	int				i;

	i = 1;
	data->vars.timeprog = taketime();
	takethreads(*data, i);
	i = 0;
	usleep(100);
	takethreads(*data, i);
	checkdeath(data);
}
