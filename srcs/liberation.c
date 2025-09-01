/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:09:17 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/02 00:41:13 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	destroy_mut(t_sup *s)
{
	int	i;

	i = 0;
	while (i < N_PHILO && s->imut_f[i] == 1)
		pthread_mutex_destroy(&s->mut_f[i++]);
	i = 0;
	while (i < N_PHILO && s->imut_lastmeal[i] == 1)
		pthread_mutex_destroy(&s->mut_lastmeal[i++]);
	i = 0;
	while (i < N_PHILO && s->imut_nmeal[i] == 1)
		pthread_mutex_destroy(&s->mut_nmeal[i++]);
	if (s->imut_end == 1)
		pthread_mutex_destroy(&s->mut_end);
	if (s->imut_write == 1)
		pthread_mutex_destroy(&s->mut_write);
	if (s->imut_start == 1)
		pthread_mutex_destroy(&s->mut_start);
	return (0);
}

int	release_all(t_sup *s, int j, int err)
{
	int	i;

	if (j != -1)
		i = j - 1;
	else
		i = s->par[0];
	while (i > 0 && s->ids[i] != NULL)
		free(s->ids[i--]);
	destroy_mut(s);
	return (err);
}
