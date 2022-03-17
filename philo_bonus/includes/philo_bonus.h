/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:21:44 by rrast             #+#    #+#             */
/*   Updated: 2022/03/16 14:23:05 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_vars
{
	int				nphilo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				numeat;
	long int		timeprog;
	sem_t			*forks;
	sem_t			*die;
	sem_t			*ate;
	sem_t			*print;
	sem_t			*timeph;
}t_vars;

typedef struct s_philo
{
	pid_t			pid;
	int				numph;
	t_vars			*vars;
	int				neat;
	long int		time;
	struct s_philo	*next;
}t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	struct s_vars	vars;
}t_data;

int			check_arg(char *str);
void		takearg(int argc, char **argv, t_vars *vars);
int			initphilo(t_data *data);
void		threads(t_data *data);
long int	taketime(void);
void		ft_usleep(long int t);
void		freedata(t_data *data);
void		ft_myprint(char *str, t_philo *philo);
void		ft_unlink(void);
void		cheackall(t_data *data);

#endif