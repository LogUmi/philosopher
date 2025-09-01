/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:34:54 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/02 00:47:26 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*justone(t_tab *t)
{
	get_pmsg(t, "has taken a fork\n", 0, 0);
	while (is_end(NULL, t) == 0)
		usleep(1000);
	return (NULL);
}

static void	go_sleep(t_tab *t)
{
	get_pmsg(t, "is sleeping\n", 0, 0);
	usleep(t->par[3] * 1000);
}

static void	go_eat(t_tab *t)
{
	long long	k;

	k = get_pmsg(t, "is eating\n", 0, 0);
	pthread_mutex_lock(t->mut_lastmeal);
	(*t->lastmeal) = k;
	pthread_mutex_unlock(t->mut_lastmeal);
	usleep(t->par[2] * 1000);
	if ((t->id % 2) == 0)
	{
		pthread_mutex_unlock(t->mut_rf);
		pthread_mutex_unlock(t->mut_lf);
	}
	else
	{
		pthread_mutex_unlock(t->mut_lf);
		pthread_mutex_unlock(t->mut_rf);
	}
	pthread_mutex_lock(t->mut_nmeal);
	if ((*t->nmeal) > 0)
		(*t->nmeal)--;
	pthread_mutex_unlock(t->mut_nmeal);
}

static void	take_forks(t_tab *t)
{
	if ((t->id % 2) != 0 && is_end(NULL, t) == 0)
	{
		pthread_mutex_lock(t->mut_rf);
		if (is_end(NULL, t) != 0)
			return (release_end(t, 0));
		get_pmsg(t, "has taken a fork\n", 0, 0);
		pthread_mutex_lock(t->mut_lf);
		if (is_end(NULL, t) != 0)
			return (release_end(t, 1));
		get_pmsg(t, "has taken a fork\n", 0, 0);
	}
	else if ((t->id % 2) == 0 && is_end(NULL, t) == 0)
	{
		pthread_mutex_lock(t->mut_lf);
		if (is_end(NULL, t) != 0)
			return (release_end(t, 2));
		get_pmsg(t, "has taken a fork\n", 0, 0);
		pthread_mutex_lock(t->mut_rf);
		if (is_end(NULL, t) != 0)
			return (release_end(t, 3));
		get_pmsg(t, "has taken a fork\n", 0, 0);
	}
}

void	*phil(void *arg)
{
	t_tab		*t;
	int			thk;

	t = (t_tab *)arg;
	thk = (t->par[1] - t->par[2] - t->par[3] - 10) * 1000;
	if (thk < 1)
		thk = 1000;
	while (is_start(NULL, t) == -1 && is_end(NULL, t) == 0)
		usleep(200);
	if (t->par[0] == 1)
		return (justone(t));
	while (is_end(NULL, t) == 0)
	{
		take_forks(t);
		if (is_end(NULL, t) == 0)
			go_eat(t);
		if (is_end(NULL, t) == 0)
			go_sleep(t);
		if (is_end(NULL, t) == 0)
		{
			get_pmsg(t, "is thinking\n", 0, 0);
			usleep(thk);
		}
	}
	return (NULL);
}
