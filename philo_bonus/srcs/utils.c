/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:45:50 by rrast             #+#    #+#             */
/*   Updated: 2022/03/16 13:51:32 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_myprint(char *str, t_philo *philo)
{
	sem_wait(philo->vars->print);
	printf("%ld %d %s\n", \
		taketime() - philo->vars->timeprog, philo->numph, str);
	sem_post(philo->vars->print);
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

void	cheackall(t_data *data)
{
	pid_t	eat;

	if (data->vars.numeat > 0)
	{
		eat = fork();
		if (eat == 0)
		{
			while (data->vars.nphilo-- > 0)
				sem_wait(data->vars.ate);
			sem_post(data->vars.die);
		}
		else
			sem_wait(data->vars.die);
	}
	else
		sem_wait(data->vars.die);
}
