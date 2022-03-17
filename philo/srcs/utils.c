/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:45:50 by rrast             #+#    #+#             */
/*   Updated: 2022/02/25 11:54:40 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_myprint(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->mutex);
	printf("%ld %d %s\n", \
		taketime() - philo->vars->timeprog, philo->numph, str);
	pthread_mutex_unlock(&philo->vars->mutex);
}

long int	taketime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long int t)
{
	long int	i;

	i = taketime();
	while (taketime() < i + t)
		usleep(250);
}

void	checkdeath(t_data *data)
{
	t_philo		*p;

	p = data->philo;
	while (1)
	{
		pthread_mutex_lock(&data->vars.lockdie);
		pthread_mutex_lock(&data->vars.alleating);
		if (data->vars.die == 0 || data->vars.alleat == 0)
		{
			while (p)
			{
				pthread_detach(p->tid);
				pthread_detach(p->tideath);
				p = p->next;
			}
			break ;
		}
		pthread_mutex_unlock(&data->vars.alleating);
		pthread_mutex_unlock(&data->vars.lockdie);
		usleep(100);
	}
}
