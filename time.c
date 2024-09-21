/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:43:59 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 16:00:46 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	convtime(struct timeval time, struct timeval time_start)
{
	unsigned long	ms;
	unsigned long	ms_start;

	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	ms_start = time_start.tv_sec * 1000 + time_start.tv_usec / 1000;
	return (ms - ms_start);
}

long	timediff(struct timeval time1, struct timeval time2)
{
	unsigned long	ms1;
	unsigned long	ms2;

	ms1 = time1.tv_sec * 1000 + time1.tv_usec / 1000;
	ms2 = time2.tv_sec * 1000 + time2.tv_usec / 1000;
	return (ms2 - ms1);
}
