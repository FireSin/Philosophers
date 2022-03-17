/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:16:25 by rrast             #+#    #+#             */
/*   Updated: 2022/02/24 13:31:21 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_vars
{
	int				nphilo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				numeat;
	int				alleat;
	pthread_mutex_t	mutex;
	pthread_mutex_t	lockdie;
	pthread_mutex_t	alleating;
	long int		timeprog;
	int				die;
}t_vars;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_t		tideath;
	int				numph;
	t_vars			*vars;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				neat;
	long int		time;
	pthread_mutex_t	tmute;
	struct s_philo	*next;
}t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	struct s_vars	vars;
	pthread_mutex_t	*forks;
}t_data;

int			check_arg(char *str);
void		takearg(int argc, char **argv, t_vars *vars);
int			initphilo(t_data *data);
void		threads(t_data *data);
long int	taketime(void);
void		ft_usleep(long int t);
void		checkdeath(t_data *data);
void		freedata(t_data *data);
void		ft_myprint(char *str, t_philo *philo);

#endif