/*
** msgout_cmd.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:19:43 2012 ulric lefevre
** Last update Sat Jun 23 20:21:53 2012 ulric lefevre
*/

#ifndef		__MSGOUT_CMD_H__
# define	__MSGOUT_CMD_H__

#include	"def.h"

void		msgout_avance(t_list*);
void		msgout_droite(t_list*);
void		msgout_gauche(t_list*);
void		msgout_voir(t_list*, char *);
void		msgout_inventaire(t_list*, t_u_inventory);
void		msgout_prend_objet(t_list*, t_bool);
void		msgout_pose_objet(t_list*, t_bool);
void		msgout_expulse(t_list*, t_bool);
void		msgout_broadcast(t_list*);
void		msgout_incantation(t_list*, int);
void		msgout_fork(t_list*);
void		msgout_connect_nbr(t_list*, char*);
void		msgout_mort(t_list*);
void		msgout_fail(t_list *);

#endif		/* !__MSGOUT_CMD_H__ */
