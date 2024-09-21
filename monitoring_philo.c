/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:11:24 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 17:25:08 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	checkdead(t_philo *philo)
{
	struct timeval	t_now;
	struct timeval	t_ate;

	t_ate = philo->ts_ate;
	if (t_ate.tv_sec == 0)
		t_ate = philo->start;
	gettimeofday(&t_now, NULL);
	if (timediff(t_ate, t_now) >= philo->t_die)
	{
		sem_wait(philo->sem_print);
		print(DIED, t_now, philo);
		sem_post(philo->sem_death);
		return (DEAD);
	}
	return (ALIVE);
}

void	*monitorphilo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		sem_wait(philo->sem_status);
		if (checkdead(philo) == DEAD)
			break ;
		sem_post(philo->sem_status);
		sem_wait(philo->sem_status);
		if (philo->status == ALIVE && philo->n_eat > 0 && \
		philo->n_ate >= philo->n_eat)
		{
			philo->status = FULL;
			sem_post(philo->sem_ate);
		}
		sem_post(philo->sem_status);
	}
	return (NULL);
}

void	createphilotr(t_philo *philo)
{
	if (pthread_create(&philo->tr1, NULL, &monitorphilo, philo) != 0)
	{
		sem_wait(philo->sem_print);
		write(2, "Error: Failed to create thread\n", 31);
		sem_close(philo->sem_status);
		exit(EXIT_FAILURE);
	}
}
