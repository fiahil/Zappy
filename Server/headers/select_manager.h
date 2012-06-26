/*
** select_manager.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:19:14 2012 ulric lefevre
** Last update Tue Jun 26 16:12:25 2012 ulric lefevre
*/

#ifndef		__SELECT_MANAGER_H__
# define	__SELECT_MANAGER_H__

#include	"def.h"

void		select_manager(t_data_serv, t_select_manager);
t_bool		select_r_isset(t_select_manager, int);
t_bool		select_w_isset(t_select_manager, int);
void		select_del(t_data_serv, int);
void		select_add(t_select_manager, int);

#endif		/* !__SELECT_MANAGER_H__ */
