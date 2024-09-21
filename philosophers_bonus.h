/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:02:32 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 15:51:59 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>

# define ALIVE 0
# define DEAD 1
# define FULL 2
# define FAIL 3
# define SEMFORKS "Sem Forks"
# define SEMDEATH "Sem Death"
# define SEMATE "Sem Ate"
# define SEMPRINT "Sem Print"
# define EAT 0
# define FORK 1
# define SLEEP 2
# define THINK 3
# define DIED 4

typedef struct s_philo
{
	long			n_philo;
	long			n_ate;
	long			t_die;
	long			t_sleep;
	long			t_eat;
	long			n_eat;
	struct timeval	start;
	int				status;
	int				*pids;
	sem_t			*sem_forks;
	sem_t			*sem_status;
	sem_t			*sem_death;
	sem_t			*sem_print;
	sem_t			*sem_ate;
	int				index;
	struct timeval	ts_ate;
	pthread_t		tr1;
	pthread_t		tr2;
	char			*name;
}	t_philo;

int		preprocessing(t_philo *dets, int argc, char **argv);
t_philo	*createphilo(t_philo *dets);
void	clear(t_philo *dets);
long	convtime(struct timeval time, struct timeval time_start);
void	simulate(t_philo *philo);
long	timediff(struct timeval time1, struct timeval time2);
long	t_sinceate(struct timeval t_ate);
void	monitoring(t_philo *philo, t_philo *dets);
void	determineforks(t_philo *philo);
void	startmeal(t_philo *philo, int *check);
int		checkstatus(t_philo *philo);
void	initsem(t_philo *dets);
void	initobjs(t_philo *dets);
void	failedsem(t_philo *dets);
void	unlinksem(t_philo *dets);
void	*monitordeath(void *arg);
void	*monitorate(void *arg);
void	createmonitoring(t_philo *dets);
void	killprocesses(t_philo *dets, int i);
void	endparentthreads(t_philo *dets);
void	createphilotr(t_philo *philo);
int		createproc(t_philo *dets);
void	closesem(t_philo *dets);
void	genname(char *name, int i);
void	print(int action, struct timeval time, t_philo *philo);
void	initsemstatus(t_philo *dets);

#endif
