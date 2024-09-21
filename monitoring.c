/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:37:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 17:26:26 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitordeath(void *arg)
{
	int		i;
	t_philo	*dets;

	dets = (t_philo *) arg;
	i = 0;
	sem_wait(dets->sem_death);
	killprocesses(dets, dets->n_philo);
	if (dets->status == ALIVE)
	{
		dets->status = DEAD;
		while (dets->n_philo > 0 && i < dets->n_philo)
		{
			sem_post(dets->sem_ate);
			i++;
		}
	}
	return (NULL);
}

void	*monitorate(void *arg)
{
	int		i;
	t_philo	*dets;

	dets = (t_philo *) arg;
	i = 0;
	if (dets->n_eat > 0)
	{
		while (i < dets->n_philo)
		{
			sem_wait(dets->sem_ate);
			i++;
		}
		if (dets->status == ALIVE)
		{
			sem_wait(dets->sem_print);
			dets->status = FULL;
			sem_post(dets->sem_death);
		}
	}
	return (NULL);
}

void	createmonitoring(t_philo *dets)
{
	if (pthread_create(&dets->tr1, NULL, &monitordeath, dets) != 0)
	{
		write(2, "Error: Thread creation failed\n", 30);
		killprocesses(dets, dets->n_philo);
		closesem(dets);
		unlinksem(dets);
		free(dets->pids);
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&dets->tr2, NULL, &monitorate, dets) != 0)
	{
		write(2, "Error: Thread creation failed\n", 30);
		dets->status = DEAD;
		sem_post(dets->sem_death);
		pthread_join(dets->tr1, NULL);
		closesem(dets);
		unlinksem(dets);
		free(dets->pids);
		exit(EXIT_FAILURE);
	}
}
