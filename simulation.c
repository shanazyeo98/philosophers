/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:21:02 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 15:53:07 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print(int action, struct timeval time, t_philo *philo)
{
	long	timestamp;

	timestamp = convtime(time, philo->start);
	if (action != DIED)
		sem_wait(philo->sem_print);
	if (action == EAT)
		printf("%lu %d is eating\n", timestamp, philo->index);
	if (action == FORK)
		printf("%lu %d has taken a fork\n", timestamp, philo->index);
	if (action == SLEEP)
		printf("%lu %d is sleeping\n", timestamp, philo->index);
	if (action == THINK)
		printf("%lu %d is thinking\n", timestamp, philo->index);
	if (action == DIED)
		printf("%lu %d died\n", timestamp, philo->index);
	if (action != DIED)
		sem_post(philo->sem_print);
}

int	sleeping(t_philo *philo)
{
	struct timeval	t_sleep;
	struct timeval	t_think;

	gettimeofday(&t_sleep, NULL);
	print(SLEEP, t_sleep, philo);
	usleep(philo->t_sleep * 1000);
	gettimeofday(&t_think, NULL);
	print(THINK, t_think, philo);
	usleep(500);
	return (EXIT_SUCCESS);
}

void	simulate(t_philo *philo)
{
	int	stat;

	stat = 0;
	while (1)
	{
		if (stat == 0)
			startmeal(philo, &stat);
		if (philo->n_philo > 1)
			sleeping(philo);
	}
}
