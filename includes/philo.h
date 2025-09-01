/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:41:04 by lgerard           #+#    #+#             */
/*   Updated: 2025/05/08 10:26:56 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef N_PHILO
#  define N_PHILO 201
# endif

typedef struct s_tab
{
	int				id;
	int				*par;
	long long		*start_ms;
	long long		*lastmeal;
	int				*nmeal;
	int				*gomeal;
	int				*rfork;
	int				*lfork;
	int				*end;
	pthread_mutex_t	*mut_rf;
	pthread_mutex_t	*mut_lf;
	pthread_mutex_t	*mut_lastmeal;
	pthread_mutex_t	*mut_nmeal;
	pthread_mutex_t	*mut_start;
	pthread_mutex_t	*mut_end;
	pthread_mutex_t	*mut_write;
}					t_tab;

typedef struct s_sup
{
	int				par[5];
	pthread_t		threads[N_PHILO];
	t_tab			*ids[N_PHILO];
	long long		start_ms;
	long long		lastmeal[N_PHILO];
	int				nmeal[N_PHILO];
	int				forks[N_PHILO];
	int				end;
	pthread_mutex_t	mut_f[N_PHILO];
	int				imut_f[N_PHILO];
	pthread_mutex_t	mut_lastmeal[N_PHILO];
	int				imut_lastmeal[N_PHILO];
	pthread_mutex_t	mut_nmeal[N_PHILO];
	int				imut_nmeal[N_PHILO];
	pthread_mutex_t	mut_start;
	int				imut_start;
	pthread_mutex_t	mut_end;
	int				imut_end;
	pthread_mutex_t	mut_write;
	int				imut_write;
}					t_sup;

int			destroy_mut(t_sup *s);
int			init_sup(t_sup *s, int i);
int			is_end(t_sup *s, t_tab *t);
long long	is_lastmeal(t_sup *s, int id);
int			is_nmeal(t_sup *s, int id);
long long	is_start(t_sup *s, t_tab *t);
int			ft_atoi(const char *nptr);
long long	get_pmsg(t_tab *t, char *msg, int i, int j);
long long	get_smsg(t_sup *s, int id, char *msg, int i);
long long	get_time_ms(void);
void		*phil(void *arg);
int			release_all(t_sup *s, int j, int err);
void		release_end(t_tab *t, int way);
int			start_sim(t_sup *s, int i);
void		*supervisor(void *arg);
#endif