/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:17:28 by rrast             #+#    #+#             */
/*   Updated: 2022/03/16 14:20:32 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*cheackphilo(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		sem_wait(p->vars->timeph);
		if (taketime() - p->vars->timeprog - p->time >= p->vars->tdie)
		{
			sem_wait(p->vars->print);
			printf("%ld %d died\n", \
				taketime() - p->vars->timeprog, p->numph);
			sem_post(p->vars->die);
			return (NULL);
		}
		sem_post(p->vars->timeph);
		usleep(850);
	}
	return (NULL);
}

void	cheackeat(t_philo *philo)
{
	if (philo->neat > 0)
		if (--philo->neat == 0)
			sem_post(philo->vars->ate);
}

void	philoact(t_philo *philo)
{
	pthread_t	cheack;

	pthread_create(&cheack, NULL, cheackphilo, (void *)philo);
	pthread_detach(cheack);
	while (1)
	{
		if (philo->neat != 0)
		{
			sem_wait(philo->vars->forks);
			ft_myprint("has taken a fork", philo);
			sem_wait(philo->vars->forks);
			sem_wait(philo->vars->timeph);
			philo->time = taketime() - philo->vars->timeprog;
			sem_post(philo->vars->timeph);
			ft_myprint("is eating", philo);
			ft_usleep(philo->vars->teat);
			cheackeat(philo);
			sem_post(philo->vars->forks);
			sem_post(philo->vars->forks);
			ft_myprint("is sleeping", philo);
			ft_usleep(philo->vars->tsleep);
			ft_myprint("is thinking", philo);
		}
	}
}

void	threads(t_data *data)
{
	t_philo	*p;

	p = data->philo;
	ft_unlink();
	data->vars.timeph = sem_open("/timeph", O_CREAT, S_IWGRP, 1);
	data->vars.forks = sem_open("/forks", O_CREAT, S_IWGRP, data->vars.nphilo);
	data->vars.die = sem_open("/die", O_CREAT, S_IWGRP, 1);
	sem_wait(data->vars.die);
	data->vars.print = sem_open("/print", O_CREAT, S_IWGRP, 1);
	if (data->vars.numeat > 0)
	{
		data->vars.ate = sem_open("/all_eat", O_CREAT, S_IWGRP, 1);
		sem_wait(data->vars.ate);
	}
	data->vars.timeprog = taketime();
	while (p)
	{
		p->pid = fork();
		if (p->pid == 0)
			philoact(p);
		p = p->next;
		usleep(80);
	}
	cheackall(data);
}
