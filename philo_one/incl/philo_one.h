/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:44:43 by ehande            #+#    #+#             */
/*   Updated: 2021/05/23 22:08:33 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# define ERR_NUM_ARGS "error number of arguments!\n\
all 5 args:\n1) number_of_philosophers\n2) time_to_die\n\
3) time_to_eat\n4) time_to_sleep\n5) \
[number_of_times_each_philosopher_must_eat]\n"

int				g_kill;
int				g_m_t_eat;
typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_f;
	int				num_philos;
	pthread_mutex_t	*right_f;
	int				must_t_to_eat;
	long			t_to_eat;
	long			t_to_sleep;
	long			t_to_die;
	long long		last_t_eat;
	long long		f_time;
	pthread_mutex_t	*print;
}				t_philo;

typedef struct s_all
{
	int				args[6];
	pthread_t		*admin;
	pthread_t		*philos_pthread;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long			time;
	pthread_mutex_t	*print;
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
