/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:49:19 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 13:14:09 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H	
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# define ERR_PARSING "Error with args\n"
# define ERR_FORK "Error fork mutex\n"
# define ERR_TIME "Error time mutex\n"
# define ERR_MEALS "Error meals mutex\n"
# define ERR_INT "Error int mutex\n"
# define ERR_PRINT "Error print mutex\n"
# define ERR_MALLOC "Error allocating\n"
# define ERR_TH "Error creating thread\n"

typedef struct s_philo
{
	struct s_main	*ptr;
	int				id;
	pthread_t		th;
	int				l_fork;
	int				r_fork;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	meals_mutex;
	int				is_full;
}	t_philo;

typedef struct s_main
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*arr;
	int				n_philo;
	int				eat;
	int				die;
	int				sleep;
	int				max_meals;
	int				start;
	long			start_time;
	pthread_mutex_t	int_mutex;
}	t_main;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *line, char *bufr);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const	char *s1, const	char *s2);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);

int		parsing(int ac, char **av);
void	print(t_philo *philo, char *msg);
long	time_in_ms(void);
void	ft_sleep(long time_to_sleep);
void	ft_destroy(t_main *p, int i, int j, int indx);
void	destroy_forks(t_main *p, int indx);

void	update_int(pthread_mutex_t *mutex, int *nb, int new);
int		read_int(pthread_mutex_t *mutex, int *nb);
void	update_time(pthread_mutex_t *mutex, long *time, long new_time);
long	read_time(pthread_mutex_t *mutex, long *time);

int		init_philos(t_main *p);
int		allocating(t_main *p);
int		creating_mutexs(t_main *p);
int		creating_philos(t_main *p);
int		watching_dead(t_main *p);
void	*fthread(void *arg);
void	error(char *s);
#endif