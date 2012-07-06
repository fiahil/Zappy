/*
** msgout_cmd.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:19:43 2012 ulric lefevre
** Last update Fri Jul  6 11:43:38 2012 ulric lefevre
*/

#ifndef		__MSGOUT_CMD_H__
# define	__MSGOUT_CMD_H__

#include	"def.h"

void		msgout_avance(t_player);
void		msgout_droite(t_player);
void		msgout_gauche(t_player);
void		msgout_voir(t_player, char *);
void		msgout_inventaire(t_player, t_u_inventory);
void		msgout_prend_objet(t_player, t_bool);
void		msgout_pose_objet(t_player, t_bool);
void		msgout_expulse(t_player, t_bool);
void		msgout_broadcast(t_player);
void		msgout_incantation(t_player, int);
void		msgout_fork(t_player);
void		msgout_connect_nbr(t_player, char*);
void		msgout_mort(t_player);
void		msgout_fail(t_player);
void		msgout_moved(t_player, int);

#endif		/* !__MSGOUT_CMD_H__ */
