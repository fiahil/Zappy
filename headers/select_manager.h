
#ifndef		__SELECT_MANAGER_H__
# define	__SELECT_MANAGER_H__

#include	"def.h"

typedef enum e_rw { READ, WRITE } t_rw;

typedef struct	s_select
{
  fd_set	readfds;
  fd_set	writefds;
}		t_select;

void		select_manager(t_clientManager *clients, int fd);
int		select_isset(int fd, t_rw flag);
void		set_max_fd(int fd);
int		get_max_fd();

#endif		/* !__SELECT_MANAGER_H__ */
