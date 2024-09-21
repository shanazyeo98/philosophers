/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:49:20 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 16:57:30 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	closesem(t_philo *dets)
{
	sem_close(dets->sem_forks);
	sem_close(dets->sem_print);
	sem_close(dets->sem_death);
	sem_close(dets->sem_ate);
}

void	unlinksem(t_philo *dets)
{
	int		i;
	char	name[3];

	i = 0;
	while (i < dets->n_philo)
	{
		genname(name, i);
		sem_unlink(name);
		i++;
	}
	sem_unlink(SEMFORKS);
	sem_unlink(SEMPRINT);
	sem_unlink(SEMATE);
	sem_unlink(SEMDEATH);
}

void	failedsem(t_philo *dets)
{
	if (dets->index != 0)
		sem_wait(dets->sem_print);
	write(2, "Error: Failed to open semaphore\n", 32);
	if (dets->index == 0)
	{
		free(dets->pids);
		closesem(dets);
		unlinksem(dets);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	clear(t_philo *dets)
{
	free(dets->pids);
	closesem(dets);
	unlinksem(dets);
}

void	killprocesses(t_philo *dets, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		kill(dets->pids[j], SIGKILL);
		j++;
	}
}
