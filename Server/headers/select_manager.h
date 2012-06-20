
#ifndef		__SELECT_MANAGER_H__
# define	__SELECT_MANAGER_H__

#include	"def.h"

void		select_manager(t_data_serv ds, t_select_manager sm);
t_bool		select_r_isset(t_select_manager sm, int fd);
t_bool		select_w_isset(t_select_manager sm, int fd);
void		select_del(t_data_serv ds, t_select_manager sm, int fd);
void		select_add(t_select_manager sm, int fd);

#endif		/* !__SELECT_MANAGER_H__ */
