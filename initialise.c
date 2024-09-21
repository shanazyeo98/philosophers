/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:07:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 17:08:09 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	genname(char *name, int i)
{
	char	*alphanum;
	int		divcount;
	int		rem;

	alphanum = "abcdefghijklmnopqrstuvwxyz0123456789";
	rem = i % 36;
	divcount = i / 36;
	name[0] = alphanum[divcount];
	name[1] = alphanum[rem];
	name[2] = '\0';
}

void	initsemstatus(t_philo *dets)
{
	char	name[3];

	genname(name, dets->index - 1);
	dets->sem_status = sem_open(name, O_CREAT, 0644, 1);
	if (dets->sem_status == SEM_FAILED)
		failedsem(dets);
}

void	initsem(t_philo *dets)
{
	dets->sem_forks = sem_open(SEMFORKS, O_CREAT, 0644, dets->n_philo);
	if (dets->sem_forks == SEM_FAILED)
		failedsem(dets);
	dets->sem_ate = sem_open(SEMATE, O_CREAT, 0644, 0);
	if (dets->sem_ate == SEM_FAILED)
		failedsem(dets);
	dets->sem_death = sem_open(SEMDEATH, O_CREAT, 0644, 0);
	if (dets->sem_death == SEM_FAILED)
		failedsem(dets);
	dets->sem_print = sem_open(SEMPRINT, O_CREAT, 0644, 1);
	if (dets->sem_print == SEM_FAILED)
		failedsem(dets);
}

void	initobjs(t_philo *dets)
{
	dets->pids = malloc(sizeof(int) * dets->n_philo);
	if (dets->pids == NULL)
	{
		write(2, "Error: Memory allocation failed\n", 32);
		exit(EXIT_FAILURE);
	}
	memset(dets->pids, 0, sizeof(int) * dets->n_philo);
	unlinksem(dets);
	initsem(dets);
}

int	createproc(t_philo *dets)
{
	int	i;
	int	pid;

	i = 0;
	gettimeofday(&dets->start, NULL);
	while (i < dets->n_philo)
	{
		pid = fork();
		if (pid == -1)
		{
			write(2, "Error: Failed to create child process\n", 38);
			killprocesses(dets, i);
			clear(dets);
			exit(EXIT_FAILURE);
		}
		else if (pid != 0)
			dets->pids[i] = pid;
		else
		{
			dets->index = i + 1;
			break ;
		}
		i++;
	}
	return (pid);
}
