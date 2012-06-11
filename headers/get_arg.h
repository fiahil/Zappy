
#ifndef		__GET_ARG_H__
# define	__GET_ARG_H__

#include	"c_lists.h"

typedef struct	s_arg
{
  int		port;
  int		width;
  int		height;
  t_list	*names_of_teams;
  int		nb_per_team;
  int		exec_time;
}		t_arg;

typedef struct	s_opt
{
  char		opt;
  void		(*ptr_func)(t_arg*);
}		t_opt;

int		get_arg(int, char **, t_arg *);
void		get_opt_c(t_arg *);
void		get_opt_n(char **, t_arg *);
void		get_opt_p(t_arg *);
void		get_opt_t(t_arg *);
void		get_opt_x(t_arg *);
void		get_opt_y(t_arg *);
void		usage();

#endif		/* !__GET_ARG_H__ */
