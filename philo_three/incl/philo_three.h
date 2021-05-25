/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:44:43 by ehande            #+#    #+#             */
/*   Updated: 2021/05/23 22:08:22 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>
# define ERR_NUM_ARGS "error number of arguments!\n\
all 5 args:\n1) number_of_philosophers\n2) time_to_die\n\
3) time_to_eat\n4) time_to_sleep\n5) \
[number_of_times_each_philosopher_must_eat]\n"

int				g_kill;
typedef struct s_philo
{
	int				id;
	int				m_t_eat;
	int				num_philos;
	int				must_t_to_eat;
	long			t_to_eat;
	long			t_to_sleep;
	long			t_to_die;
	long long		last_t_eat;
	long long		f_time;
	sem_t			*forks;
	sem_t			*print;
}				t_philo;

typedef struct s_all
{
	int				args[6];
	pthread_t		*admin;
	pthread_t		*philos_pthread;
	t_philo			*philos;
	long			time;
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*print;
}					t_all;

size_t			w(char *str);
size_t			ft_strlen(const char *s);
void			finish(char *str);
int				ft_atoi(const char *str);
void			init(t_all *all);
void			run_simulation(t_all *all);
long long		get_time_in_ms(void);
void			www_stop(long long time);
void			print(int id, char *log, t_philo *phi);
char			*ft_strcpy(char *dest, char *src);
int				get_min(int a, int b);
int				get_max(int a, int b);
int				ft_atoi(const char *str);
void			*check_death(void *philo);
void			*eat_sleep_think(void *philo_void);
void			free_pthread(pthread_t *p, pthread_t *w, int nb);
#endif
